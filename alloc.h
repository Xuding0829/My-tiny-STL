#ifndef ALLOC_H_
#define ALLOC_H_

#include <iostream>
#include <cstddef>
#include <cstdlib>

namespace mystd
{
    template <int inst>
    class malloc_alloc_template
    {
    private:
        static void *oom_malloc(size_t);
        static void *oom_realloc(void *, size_t);
        static void (*malloc_alloc_oom_handler)();

    public:
        static void *allocate(size_t);
        static void *reallocate(void *, size_t, size_t);
        static void deallocate(void *, size_t);
        static void (*set_malloc_handler(void (*)()))();
    };

    template <int inst>
    void *malloc_alloc_template<inst>::oom_malloc(size_t size)
    {
        void (*my_malloc_handler)();
        void *result;

        for (;;)
        {
            my_malloc_handler = malloc_alloc_oom_handler;
            if (my_malloc_handler == 0)
            {
                std::cout << "out of memory!" << std::endl;
                exit(1);
            }

            (*my_malloc_handler)();
            result = malloc(size);
            if (result)
                return result;
        }
    }

    template <int inst>
    void *malloc_alloc_template<inst>::oom_realloc(void *p, size_t size)
    {
        void (*my_malloc_handler)();
        void *result;

        for (;;)
        {
            my_malloc_handler = malloc_alloc_oom_handler;
            if (my_malloc_handler == 0)
            {
                std::cout << "out of memory!" << std::endl;
                exit(1);
            }

            (*my_malloc_handler)();
            result = realloc(p, size);
            if (result)
                return result;
        }
    }

    template <int inst>
    void (*malloc_alloc_template<inst>::malloc_alloc_oom_handler)() = nullptr;

    template <int inst>
    void *malloc_alloc_template<inst>::allocate(size_t size)
    {
        void *result = malloc(size);
        if (result == 0)
            result = oom_malloc(size);
        return result;
    }

    template <int inst>
    void *malloc_alloc_template<inst>::reallocate(void *p, size_t, size_t new_size)
    {
        void *result = realloc(p, new_size);
        if (result == 0)
            result = oom_realloc(p, new_size);
        return result;
    }

    template <int inst>
    void malloc_alloc_template<inst>::deallocate(void *p, size_t)
    {
        free(p);
    }

    template <int inst>
    void (*malloc_alloc_template<inst>::set_malloc_handler(void (*f)()))()
    {
        void (*old)() = malloc_alloc_oom_handler;
        malloc_alloc_oom_handler = f;
        return (old);
    }

    typedef malloc_alloc_template<0> malloc_alloc;

    template <class T, class Alloc>
    class simple_alloc
    {
    public:
        static T *allocate(size_t n);
        static T *allocate(void);
        static void deallocate(T *p, size_t n);
        static void deallocate(T *p);
    };

    template <class T, class Alloc>
    T *simple_alloc<T, Alloc>::allocate(size_t n)
    {
        return n == 0 ? 0 : (T *)Alloc::allocate(n * sizeof(T));
    }

    template <class T, class Alloc>
    T *simple_alloc<T, Alloc>::allocate(void)
    {
        return (T *)Alloc::allocate(sizeof(T));
    }

    template <class T, class Alloc>
    void simple_alloc<T, Alloc>::deallocate(T *p, size_t n)
    {
        if (n != 0)
            Alloc::deallocate(p, n * sizeof(T));
    }

    template <class T, class Alloc>
    void simple_alloc<T, Alloc>::deallocate(T *p)
    {
        Alloc::deallocate(p, sizeof(T));
    }

    template <int inst>
    class default_alloc_template
    {
    private:
        static const int ALIGN = 8;
        static const int MAX_BYTES = 128;
        static const int NFREELISTS = 16;

        union obj
        {
            union obj *free_list_link;
            char client_data[1];
        };

        static obj *free_list[NFREELISTS];

        static char *start_free;
        static char *end_free;
        static size_t heap_size;

        static size_t ROUND_UP(size_t bytes) { return ((bytes + ALIGN - 1) & ~(ALIGN - 1)); }
        static size_t FREELIST_INDEX(size_t bytes) { return ((bytes + ALIGN - 1) / ALIGN - 1); }

        static void *refill(size_t n);
        static char *chunk_alloc(size_t size, int &nobjs);

    public:
        static void *allocate(size_t);
        static void deallocate(void *, size_t);
        static void *reallocate(void *, size_t, size_t);
    };

    typedef default_alloc_template<0> alloc;
    typedef default_alloc_template<0> single_client_alloc;

    template <int inst>
    void *default_alloc_template<inst>::allocate(size_t size)
    {
        if (size > MAX_BYTES)
        {
            return malloc_alloc_template<inst>::allocate(size);
        }

        int index = FREELIST_INDEX(size);
        obj *result = free_list[index];
        if (result == 0)
        {
            void *r = refill(ROUND_UP(size));
            return r;
        }
        free_list[index] = result->free_list_link;
        return result;
    }

    template <int inst>
    void default_alloc_template<inst>::deallocate(void *p, size_t size)
    {
        if (size > MAX_BYTES)
        {
            malloc_alloc_template<inst>::deallocate(p, size);
            return;
        }

        int index = FREELIST_INDEX(size);
        ((obj*)p)->free_list_link = free_list[index];
        free_list[index] = (obj *)p;
    }

    template <int inst>
    void *default_alloc_template<inst>::reallocate(void *p, size_t old_size, size_t new_size)
    {
        if (old_size > MAX_BYTES && new_size > MAX_BYTES)
            return (malloc_alloc_template<inst>::reallocate(p, new_size));

        if (ROUND_UP(old_size) == ROUND_UP(new_size))
            return p;

        void *result = allocate(new_size);
        size_t copy_size = new_size > old_size ? new_size : old_size;
        memcpy(result, p, copy_size);
        deallocate(p, old_size);
        return result;
    }

    template <int inst>
    void *default_alloc_template<inst>::refill(size_t n)
    {
        int nobjs = 20;
        char *chunk = chunk_alloc(n, nobjs);

        if (nobjs == 1)
            return chunk;

        int index = FREELIST_INDEX(n);
        obj *current_obj = (obj *)(chunk + n);
        obj *next_obj = (obj *)((char *)current_obj + n);

        while (--nobjs)
        {
            current_obj->free_list_link = free_list[index];
            free_list[index] = current_obj;
            current_obj = next_obj;
            next_obj = (obj *)((char *)next_obj + n);
        }
        return chunk;
    }

    template <int inst>
    char *default_alloc_template<inst>::chunk_alloc(size_t size, int &nobjs)
    {
        char *result;
        size_t totol_bytes = size * nobjs;
        size_t bytes_left = end_free - start_free;

        if (bytes_left > totol_bytes)
        {
            result = start_free;
            start_free += totol_bytes;
            return result;
        }
        else if (bytes_left >= size)
        {
            nobjs = int(bytes_left / size);
            totol_bytes = nobjs * size;
            result = start_free;
            start_free += totol_bytes;
            return result;
        }
        else
        {
            size_t bytes_to_get = 2 * totol_bytes + ROUND_UP(heap_size >> 4);

            if (bytes_left > 0)
            {
                obj **my_free_list = free_list + FREELIST_INDEX(bytes_left);
                ((obj *)start_free)->free_list_link = *my_free_list;
                *my_free_list = (obj *)start_free;
            }

            start_free = (char *)malloc(bytes_to_get);
            obj **my_free_list, *p;
            if (start_free == 0)
            {
                for (int i = size; i <= MAX_BYTES; i += ALIGN)
                {
                    my_free_list = free_list + FREELIST_INDEX(i);
                    p = *my_free_list;
                    if(p)
                    {
                        *my_free_list = p->free_list_link;
                        start_free = (char*) p;
                        end_free = start_free + i;
                        return(chunk_alloc(size, nobjs));
                    }
                }
                end_free = 0;
                start_free = (char*)malloc_alloc_template<inst>::allocate(bytes_to_get);
            }

            heap_size += bytes_to_get;
            end_free = start_free + bytes_to_get;
            return chunk_alloc(size, nobjs);
        }
    }

    template <int inst>
    char *default_alloc_template<inst>::start_free = nullptr;

    template <int inst>
    char *default_alloc_template<inst>::end_free = nullptr;

    template <int inst>
    size_t default_alloc_template<inst>::heap_size = 0;

    template <int inst>
    typename default_alloc_template<inst>::obj *
        default_alloc_template<inst>::free_list[default_alloc_template<inst>::NFREELISTS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

};

#endif
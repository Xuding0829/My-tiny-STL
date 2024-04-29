#ifndef CONSTRUCT_H_
#define CONSTRUCT_H_

#include <new>
#include "iterator.h"
#include "type_traits.h"

namespace mystd
{
    template <class T1, class T2>
    inline void construct(T1 *p, const T2 &value)
    {
        new (p) T1(value);
    }

    template <class T>
    inline void destroy(T *p)
    {
        p->~T();
    }

    template <class iterator>
    inline void destroy_aux(iterator first, iterator last, __false_type)
    {
        for (; first < last; first++)
            destroy(&*first);
    }

    template <class iterator>
    inline void destroy_aux(iterator first, iterator last, __true_type) {}

    template <class iterator, class T>
    inline void _destroy(iterator first, iterator last, T *)
    {
        typedef typename __type_traits<T>::has_trivial_destructor trivial_destructor;
        destroy_aux(first, last, trivial_destructor());
    }

    template <class iterator>
    inline void destroy(iterator first, iterator last)
    {
        destroy(first, last, value_type(first));
    }

    inline void destroy(char *, char *) {}
    inline void destroy(wchar_t *, wchar_t *) {}
};

#endif

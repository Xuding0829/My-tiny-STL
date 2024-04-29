#ifndef UNINITIALIZED_H_
#define UNINITIALIZED_H_

#include "construct.h"
#include "algorithm.h"
#include "pair.h"

namespace mystd
{
    template <class iterator>
    inline iterator uninitialized_copy_aux(iterator first, iterator last, iterator result, __true_type)
    {
        return mystd::copy(first, last, result);
    }

    template <class iterator>
    iterator uninitialized_copy_aux(iterator first, iterator last, iterator result, __false_type)
    {
        iterator cur = result;
        try
        {
            for (; first != last; ++first, ++cur)
                construct(&*cur, *first);
            return cur;
        }
        catch (...)
        {
            destroy(result, cur);
            throw;
        }
    }

    template <class iterator, class T>
    inline iterator uninitialized_copy(iterator first, iterator last, iterator result, T *)
    {
        typedef typename __type_traits<T>::is_POD_type is_POD;
        return uninitialized_copy_aux(first, last, result, is_POD());
    }

    template <class iterator>
    inline iterator uninitialized_copy(iterator first, iterator last, iterator result)
    {

        return uninitialized_copy(first, last, result, value_type(result));
    }

    inline char *uninitialized_copy(const char *first, const char *last, char *result)
    {
        memmove(result, first, last - first);
        return result + (last - first);
    }

    inline wchar_t *uninitialized_copy(const wchar_t *first, const wchar_t *last, wchar_t *result)
    {
        memmove(result, first, sizeof(wchar_t) * (last - first));
        return result + (last - first);
    }

    template <class iterator, class size>
    mystd::pair<iterator, iterator> uninitialized_copy_n(iterator first, size count, iterator result, input_iterator_tag)
    {
        iterator cur = result;
        try
        {
            for (; count > 0; --count, ++first, ++cur)
                construct(&*cur, *first);
            return mystd::pair<iterator, iterator>(first, cur);
        }
        catch (...)
        {
            destroy(result, cur);
            throw;
        }
    }

    template <class iterator, class size>
    inline pair<iterator, iterator> uninitialized_copy_n(iterator first, size count, iterator result, random_access_iterator_tag)
    {
        iterator last = first + count;
        return make_pair(last, uninitialized_copy(first, last, result));
    }

    template <class iterator, class size>
    inline mystd::pair<iterator, iterator> uninitialized_copy_n(iterator first, size count, iterator result)
    {
        return uninitialized_copy_n(first, count, result, iterator_category(first));
    }

    template <class iterator, class T>
    inline void uninitialized_fill_aux(iterator first, iterator last, const T &x, __true_type)
    {
        fill(first, last, x);
    }

    template <class iterator, class T>
    void uninitialized_fill_aux(iterator first, iterator last, const T &x, __false_type)
    {
        iterator cur = first;
        try
        {
            for (; cur != last; ++cur)
                construct(&*cur, x); // 必须一个一个元素地建构，无法批量进行
        }
        catch (...)
        {
            destroy(first, cur);
            throw;
        }
    }

    template <class iterator, class T, class T1>
    inline void uninitialized_fill(iterator first, iterator last, const T &x, T1 *)
    {
        typedef typename __type_traits<T1>::is_POD_type is_POD;
        uninitialized_fill_aux(first, last, x, is_POD());
    }

    template <class iterator, class T>
    inline void uninitialized_fill(iterator first, iterator last, const T &x)
    {
        uninitialized_fill(first, last, x, value_type(first));
    }

    template <class iterator, class size, class T>
    inline iterator uninitialized_fill_n_aux(iterator first, size n, const T &x, __true_type)
    {
        return mystd::fill_n(first, n, x);
    }

    template <class iterator, class size, class T>
    iterator uninitialized_fill_n_aux(iterator first, size n, const T &x, __false_type)
    {
        iterator cur = first;
        try
        {
            for (; n > 0; --n, ++cur)
                construct(&*cur, x);
            return cur;
        }
        catch (...)
        {
            destroy(first, cur);
            throw;
        }
    }

    template <class iterator, class size, class T, class T1>
    inline iterator uninitialized_fill_n(iterator first, size n, const T &x, T1 *)
    {
        typedef typename __type_traits<T1>::is_POD_type is_POD;
        return uninitialized_fill_n_aux(first, n, x, is_POD());
    }

    template <class iterator, class size, class T>
    inline iterator uninitialized_fill_n(iterator first, size n, const T &x)
    {
        return uninitialized_fill_n(first, n, x, value_type(first));
    }

    template <class iterator>
    inline iterator uninitialized_copy_copy(iterator first1, iterator last1, iterator first2, iterator last2, iterator result)
    {
        iterator mid = uninitialized_copy(first1, last1, result);
        try
        {
            return uninitialized_copy(first2, last2, mid);
        }
        catch (...)
        {
            destroy(result, mid);
            throw;
        }
    }

    template <class iterator, class T>
    inline iterator _uninitialized_fill_copy(iterator result, iterator mid, const T &x, iterator first, iterator last)
    {
        uninitialized_fill(result, mid, x);
        try
        {
            return uninitialized_copy(first, last, mid);
        }
        catch (...)
        {
            destroy(result, mid);
            throw;
        }
    }

    template <class iterator, class T>
    inline void _uninitialized_copy_fill(iterator first1, iterator last1, iterator first2, iterator last2, const T &x)
    {
        iterator mid2 = uninitialized_copy(first1, last1, first2);
        try
        {
            uninitialized_fill(mid2, last2, x);
        }
        catch (...)
        {
            destroy(first2, mid2);
            throw;
        }
    }
};
#endif

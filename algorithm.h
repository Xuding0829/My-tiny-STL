#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include <stddef.h>

namespace mystd
{
    template <class T>
    inline const T &min(const T &a, const T &b)
    {
        return (a < b ? a : b);
    }

    template <class T>
    inline const T &max(const T &a, const T &b)
    {
        return (a < b ? b : a);
    }

    template <class T>
    inline void swap(T &a, T &b)
    {
        T tmp = a;
        a = b;
        b = tmp;
    }

    template <class T>
    inline T gcd(const T a, const T b)
    {
        return (b ? gcd(b, a % b) : a);
    }

    template <class T>
    inline T lcm(const T a, const T b)
    {
        return a * b / gcd(a, b);
    }

    template <class iterator, class T>
    inline void fill(iterator first, iterator last, const T &value)
    {
        while (first != last)
        {
            *first = value;
            first++;
        }
    }

    template <class iterator, class T>
    inline iterator find(iterator first, iterator last, const T &value)
    {
        while (first != last && *first != value)
            ++first;
        return first;
    }

    template <class iterator>
    inline iterator copy(iterator first, iterator last, iterator result)
    {
        while (first != last)
        {
            *result = *first;
            ++first, ++result;
        }
        return result;
    }

    template <class iterator, class size, class T>
    inline iterator fill_n(iterator first, size n, const T &value)
    {
        for (; n > 0; --n, ++first)
            *first = value;
        return first;
    }

    template <class iterator>
    inline iterator max_element(iterator first, iterator last)
    {
        if (first == last)
            return last;
        iterator result = first;
        while (++first != last)
        {
            if (*first > *result)
                result = first;
        }
        return result;
    }

    template <class iterator>
    inline iterator min_element(iterator first, iterator last)
    {
        if (first == last)
            return last;
        iterator result = first;
        while (++first != last)
        {
            if (*first < *result)
                result = first;
        }
        return result;
    }

    template <class iterator, class T>
    inline size_t count_if(iterator first, iterator last, const T &value)
    {
        size_t n = 0;
        for (; first != last; first++)
        {
            if (*first == value)
                n++;
        }
        return n;
    }
    template <class iterator, class T>
    inline void iota(iterator first, iterator last, T value)
    {
        for (; first != last; ++first)
        {
            *first = value;
            ++value;
        }
    }

    template <class iterator>
    inline bool is_sorted(iterator first, iterator last)
    {
        if (first == last)
            return true;

        iterator next = first;
        for (++next; next != last; next++)
        {
            if (*next < *first)
                return false;
        }
        return true;
    }

    template <class iterator>
    inline void sort(iterator lp, iterator rp)
    {
        --rp;
        if (rp - lp > 0)
        {
            iterator olp = lp, orp = rp;
            typename std::iterator_traits<iterator>::value_type pivot = *lp;
            while (lp != rp)
            {
                while (*rp >= pivot && rp > lp)
                    --rp;
                while (*lp <= pivot && rp > lp)
                    ++lp;
                if (rp != lp)
                    mystd::swap(*rp, *lp);
            }
            mystd::swap(*olp, *rp);
            sort(olp, lp - 1), sort(rp + 1, orp);
        }
    };
};
#endif
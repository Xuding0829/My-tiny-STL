#ifndef ITERATOR_H_
#define ITERATOR_H_

#include <cstddef>

namespace mystd
{
    struct input_iterator_tag
    {
    };
    struct output_iterator_tag
    {
    };
    struct forward_iterator_tag : public input_iterator_tag
    {
    };
    struct bidirectional_iterator_tag : public forward_iterator_tag
    {
    };
    struct random_access_iterator_tag : public bidirectional_iterator_tag
    {
    };

    template <class T, class Distance>
    struct input_iterator
    {
        typedef input_iterator_tag iterator_category;
        typedef T value_type;
        typedef Distance difference_type;
        typedef T *pointer;
        typedef T &reference;
    };

    struct output_iterator
    {
        typedef output_iterator_tag iterator_category;
        typedef void value_type;
        typedef void difference_type;
        typedef void pointer;
        typedef void reference;
    };

    template <class T, class Distance>
    struct forward_iterator
    {
        typedef forward_iterator_tag iterator_category;
        typedef T value_type;
        typedef Distance difference_type;
        typedef T *pointer;
        typedef T &reference;
    };

    template <class T, class Distance>
    struct bidirectional_iterator
    {
        typedef bidirectional_iterator_tag iterator_category;
        typedef T value_type;
        typedef Distance difference_type;
        typedef T *pointer;
        typedef T &reference;
    };

    template <class T, class Distance>
    struct random_access_iterator
    {
        typedef random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef Distance difference_type;
        typedef T *pointer;
        typedef T &reference;
    };

    template <class Category, class T, class Distance = ptrdiff_t,
              class pointer = T *, class reference = T &>
    struct iterator
    {
        typedef Category iterator_category;
        typedef T value_type;
        typedef Distance difference_type;
    };

    template <class iterator>
    struct iterator_traits
    {
        typedef typename iterator::iterator_category iterator_category;
        typedef typename iterator::value_type value_type;
        typedef typename iterator::difference_type difference_type;
        typedef typename iterator::pointer pointer;
        typedef typename iterator::reference reference;
    };

    template <class T>
    struct iterator_traits<T *>
    {
        typedef random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T *pointer;
        typedef T &reference;
    };

    template <class T>
    struct iterator_traits<const T *>
    {
        typedef random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef const T *pointer;
        typedef const T &reference;
    };

    template <class iterator>
    inline typename iterator_traits<iterator>::iterator_category
    iterator_category(const iterator &)
    {
        typedef typename iterator_traits<iterator>::iterator_category category;
        return category();
    }

    template <class iterator>
    inline typename iterator_traits<iterator>::difference_type *
    distance_type(const iterator &)
    {
        return static_cast<typename iterator_traits<iterator>::difference_type *>(0);
    }

    template <class iterator>
    inline typename iterator_traits<iterator>::value_type *value_type(const iterator &)
    {
        return static_cast<typename iterator_traits<iterator>::value_type *>(0);
    }

    template <class iterator>
    inline typename iterator_traits<iterator>::difference_type distance(iterator first, iterator last, input_iterator_tag)
    {
        typename iterator_traits<iterator>::difference_type n = 0;
        while (first != last)
        {
            ++first;
            ++n;
        }
        return n;
    }

    template <class iterator>
    inline typename iterator_traits<iterator>::difference_type distance(iterator first, iterator last, random_access_iterator_tag)
    {
        return last - first;
    }

    template <class iterator>
    inline
        typename iterator_traits<iterator>::difference_type
        distance(iterator first, iterator last)
    {
        typedef typename iterator_traits<iterator>::iterator_category category;
        return distance(first, last, category());
    }

    template <class iterator, class Distance>
    inline void advance(iterator &i, Distance n, input_iterator_tag)
    {
        while (n--)
            ++i;
    }

    template <class iterator, class Distance>
    inline void advance(iterator &i, Distance n, bidirectional_iterator_tag)
    {
        if (n >= 0)
            while (n--)
                ++i;
        else
            while (n++)
                --i;
    }

    template <class iterator, class Distance>
    inline void advance(iterator &i, Distance n, random_access_iterator_tag)
    {
        i += n;
    }

    template <class iterator, class Distance>
    inline void advance(iterator &i, Distance n)
    {
        advance(i, n, iterator_category(i));
    }
};

#endif

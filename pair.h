#ifndef PAIR_H_
#define PAIR_H_

namespace mystd
{
    template <class T1, class T2>
    struct pair
    {
        T1 first;
        T2 second;

        pair() : first(T1()), second(T2()) {}
        pair(const T1 &a, const T2 &b) : first(a), second(b) {}
        pair(const pair<T1, T2> &p) : first(p.first), second(p.second){};

        bool operator==(const pair<T1, T2> &x) const
        {
            return this->first == x.first && this->second == x.second;
        }

        bool operator<(const pair<T1, T2> &x) const
        {
            return (this->first < x.first || (this->first == x.first && this->second < x.second));
        }

        pair<T1, T2> make_pair(const T1 &x, const T2 &y) 
        {
            return pair<T1, T2>(x, y);
        }
    };
};

#endif
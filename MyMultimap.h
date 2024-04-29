#ifndef _MYMULTIMAP_H_
#define _MYMULTIMAP_H_

#include <iostream>
#include <map>
#include <utility>
using namespace std;


template <typename Key, typename T>
class MyMultimap {
private:
    map<Key, multimap<Key, T>> data;

public:
    using value_type = pair<const Key, T>;

    // ����Ԫ��
    void insert(const value_type& value) {
        data[value.first].insert(value);
    }

    // ɾ��Ԫ��
    void erase(const Key& key) {
        auto it = data.find(key);
        if (it != data.end()) {
            it->second.clear();
            data.erase(it);
        }
    }

    // ����Ԫ��
    auto find(const Key& key) const {
        auto it = data.find(key);
        if (it != data.end()) {
            return Iterator(it, data.end());
        }
        return end();
    }

    // ��ȡ������С
    size_t size() const {
        std::size_t count = 0;
        for (const auto& pair : data) {
            count += pair.second.size();
        }
        return count;
    }

    // ��������Ƿ�Ϊ��
    bool empty() const {
        return data.empty();
    }

    // �������
    void clear() {
        data.clear();
    }

    // �����������
    void print() const {
        for (const auto& pair : data) {
            for (const auto& entry : pair.second) {
                cout << pair.first << ": " << entry.second << endl;
            }
        }
    }

    // �����ض�����Ԫ������
    size_t count(const Key& key) const {
        auto it = data.find(key);
        if (it != data.end()) {
            return it->second.size();
        }
        return 0;
    }

    // ��ȡ��һ��Ԫ�صĵ�����
    auto begin() const {
        return Iterator(data.begin(), data.end());
    }

    // ��ȡβ����ĩβ���棩�ĵ�����
    auto end() const {
        return Iterator(data.end(), data.end());
    }

    class Iterator {
    private:
        using MapIterator = typename map<Key, std::multimap<Key, T>>::const_iterator;
        using MultiMapIterator = typename std::multimap<Key, T>::const_iterator;

        MapIterator mapIt;           // ���� map �ĵ�����
        MapIterator mapEnd;          // map ��β��������
        MultiMapIterator multiMapIt; // ���� multimap �ĵ�����

    public:
        Iterator(MapIterator begin, MapIterator end)
            : mapIt(begin), mapEnd(end) {
            // ��� map ��Ϊ�գ���ʼ�� multimap �ĵ�����
            if (mapIt != mapEnd && !mapIt->second.empty()) {
                multiMapIt = mapIt->second.begin();
            }
        }

        // ǰ׺����������
        Iterator& operator++() {
            // ��� multimap ������δ�ﵽ multimap ��β������������
            if (multiMapIt != mapIt->second.end()) {
                ++multiMapIt;
            }
            // �����ƶ�����һ�� map ��Ԫ��
            else {
                ++mapIt;
                // ��� map ������δ�ﵽ map ��β������ʼ�� multimap �ĵ�����
                if (mapIt != mapEnd && !mapIt->second.empty()) {
                    multiMapIt = mapIt->second.begin();
                }
            }
            return *this;
        }

        // ��׺����������
        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        // �����ò�����
        const value_type& operator*() const {
            return *multiMapIt;
        }

        // ����� -> ����
        const value_type* operator->() const {
            return &(*multiMapIt);
        }

        // �Ƚϲ�����
        bool operator!=(const Iterator& other) const {
            return mapIt != other.mapIt || (mapIt != mapEnd && multiMapIt != other.multiMapIt);
        }
    };
};

#endif 
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

    // 插入元素
    void insert(const value_type& value) {
        data[value.first].insert(value);
    }

    // 删除元素
    void erase(const Key& key) {
        auto it = data.find(key);
        if (it != data.end()) {
            it->second.clear();
            data.erase(it);
        }
    }

    // 查找元素
    auto find(const Key& key) const {
        auto it = data.find(key);
        if (it != data.end()) {
            return Iterator(it, data.end());
        }
        return end();
    }

    // 获取容器大小
    size_t size() const {
        std::size_t count = 0;
        for (const auto& pair : data) {
            count += pair.second.size();
        }
        return count;
    }

    // 检查容器是否为空
    bool empty() const {
        return data.empty();
    }

    // 清空容器
    void clear() {
        data.clear();
    }

    // 输出容器内容
    void print() const {
        for (const auto& pair : data) {
            for (const auto& entry : pair.second) {
                cout << pair.first << ": " << entry.second << endl;
            }
        }
    }

    // 计算特定键的元素数量
    size_t count(const Key& key) const {
        auto it = data.find(key);
        if (it != data.end()) {
            return it->second.size();
        }
        return 0;
    }

    // 获取第一个元素的迭代器
    auto begin() const {
        return Iterator(data.begin(), data.end());
    }

    // 获取尾部（末尾后面）的迭代器
    auto end() const {
        return Iterator(data.end(), data.end());
    }

    class Iterator {
    private:
        using MapIterator = typename map<Key, std::multimap<Key, T>>::const_iterator;
        using MultiMapIterator = typename std::multimap<Key, T>::const_iterator;

        MapIterator mapIt;           // 迭代 map 的迭代器
        MapIterator mapEnd;          // map 的尾部迭代器
        MultiMapIterator multiMapIt; // 迭代 multimap 的迭代器

    public:
        Iterator(MapIterator begin, MapIterator end)
            : mapIt(begin), mapEnd(end) {
            // 如果 map 不为空，初始化 multimap 的迭代器
            if (mapIt != mapEnd && !mapIt->second.empty()) {
                multiMapIt = mapIt->second.begin();
            }
        }

        // 前缀递增操作符
        Iterator& operator++() {
            // 如果 multimap 迭代器未达到 multimap 的尾部，继续递增
            if (multiMapIt != mapIt->second.end()) {
                ++multiMapIt;
            }
            // 否则，移动到下一个 map 的元素
            else {
                ++mapIt;
                // 如果 map 迭代器未达到 map 的尾部，初始化 multimap 的迭代器
                if (mapIt != mapEnd && !mapIt->second.empty()) {
                    multiMapIt = mapIt->second.begin();
                }
            }
            return *this;
        }

        // 后缀递增操作符
        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        // 解引用操作符
        const value_type& operator*() const {
            return *multiMapIt;
        }

        // 运算符 -> 重载
        const value_type* operator->() const {
            return &(*multiMapIt);
        }

        // 比较操作符
        bool operator!=(const Iterator& other) const {
            return mapIt != other.mapIt || (mapIt != mapEnd && multiMapIt != other.multiMapIt);
        }
    };
};

#endif 
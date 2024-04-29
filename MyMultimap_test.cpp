#include <iostream>
#include "MyMultimap.h"
using namespace std;

int main() {
    MyMultimap<int, string> myMultimap;

    myMultimap.insert({ 1, "apple" });
    myMultimap.insert({ 2, "banana" });
    myMultimap.insert({ 1, "avocado" });

    // 使用迭代器遍历 MyMultimap
    cout << "Original Multimap:\n";
    myMultimap.print();

    // 查找并删除键为1的所有元素
    myMultimap.erase(1);

    cout << "\nMultimap after erasing elements with key 1:\n";
    myMultimap.print();

    // 查找键为2的元素
    auto it = myMultimap.find(2);
    if (it != myMultimap.end()) {
        cout << "\nElement with key 2 found: " << it->second << endl;
    }
    else {
        cout << "\nElement with key 2 not found\n";
    }

    // 获取容器大小
    cout << "\nSize of Multimap: " << myMultimap.size() << endl;

    // 检查容器是否为空
    cout << "Is Multimap empty? " << (myMultimap.empty() ? "Yes" : "No") << endl;

    // 清空容器
    myMultimap.clear();
    cout << "\nMultimap after clearing:\n";
    myMultimap.print();

    // 计算特定键的元素数量
    cout << "\nCount of elements with key 2: " << myMultimap.count(2) << endl;

    return 0;
}
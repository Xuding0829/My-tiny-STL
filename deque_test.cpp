#include <iostream>
#include "deque.h"

int main()
{
    Deque<int> myDeque;
    std::cout << "已定义myDeque, 下面将对内部函数及迭代器进行测试。\n\n";
    
    // push_back
    std::cout << "末尾按顺序插入4, 8, 2\n";
    myDeque.push_back(4);
    myDeque.push_back(8);
    myDeque.push_back(2);

    // push_front
    std::cout << "队头按顺序插入9, 3, 7\n\n";
    myDeque.push_front(9);
    myDeque.push_front(3);
    myDeque.push_front(7);

    // 迭代器、++重载、解引用、begin、end
    std::cout << "从前往后遍历myDeque: ";
    for (DequeIterator<int> it = myDeque.begin(); it != myDeque.end(); ++ it)
    {
        std::cout << *it << ' ';
    }
    std::cout << "\n\n";

    // 迭代器、--重载、解引用、rbegin、rend
    std::cout << "从后往前遍历myDeque: ";
    for (DequeIterator<int> it = myDeque.rbegin(); it != myDeque.rend(); -- it)
    {
        std::cout << *it << ' ';
    }
    std::cout << "\n\n";

    // =重载
    std::cout << "新定义q1 = myDeque, 输出q1: ";
    Deque<int> q1 = myDeque;
    for (DequeIterator<int> it = q1.begin(); it != q1.end(); ++ it)
    {
        std::cout << *it << ' ';
    }
    std::cout << "\n\n";

    // assign
    std::cout << "新定义q2.assign(3, 4), 输出q2: ";
    Deque<int> q2;
    q2.assign(3, 4);
    for (DequeIterator<int> it = q2.begin(); it != q2.end(); ++ it)
    {
        std::cout << *it << ' ';
    }
    std::cout << "\n";
    std::cout << "新定义q3.assign(myDeque.begin(), myDeque.end()), 输出q3: ";
    Deque<int> q3;
    q3.assign(myDeque.begin(), myDeque.end());
    for (DequeIterator<int> it = q3.begin(); it != q3.end(); ++ it)
    {
        std::cout << *it << ' ';
    }
    std::cout << "\n\n";

    // empty、resize、size
    std::cout << "判断myDeque是否为空: ";
    if (myDeque.empty()) std::cout << "是\n";
    else std::cout << "否\n";
    std::cout << "改变myDeque大小为5, 输出myDeque大小: ";
    myDeque.resize(5);
    std::cout << myDeque.size() << "\n\n";

    // pop_back、pop_front
    std::cout << "删去队头元素和队尾元素, 输出myDeque: ";
    myDeque.pop_back();
    myDeque.pop_front();
    for (DequeIterator<int> it = myDeque.begin(); it != myDeque.end(); ++ it)
    {
        std::cout << *it << ' ';
    }

    // insert、+重载
    std::cout << "在第一个元素之后插入8, 输出myDeque: ";
    DequeIterator<int> it1 = myDeque.begin() + 1;
    myDeque.insert(it1, 8);
    for (DequeIterator<int> it = myDeque.begin(); it != myDeque.end(); ++ it)
    {
        std::cout << *it << ' ';
    }
    std::cout << "\n\n";

    // erase、+重载
    std::cout << "删去第三个元素, 输出myDeque: ";
    DequeIterator<int> it2 = myDeque.begin() + 2;
    myDeque.erase(it2);
    for (DequeIterator<int> it = myDeque.begin(); it != myDeque.end(); ++ it)
    {
        std::cout << *it << ' ';
    }

    // at
    std::cout << "at返回第三个数: " << myDeque.at(2) << "\n";

    // []重载
    std::cout << "下标返回第二个数: " << myDeque[1] << "\n\n";

    // front、back
    std::cout << "输出队头和队尾: " << myDeque.front() << ' ' << myDeque.back() << "\n\n";




    return 0;
}
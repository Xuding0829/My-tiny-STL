#include <iostream>
#include "MyMultimap.h"
using namespace std;

int main() {
    MyMultimap<int, string> myMultimap;

    myMultimap.insert({ 1, "apple" });
    myMultimap.insert({ 2, "banana" });
    myMultimap.insert({ 1, "avocado" });

    // ʹ�õ��������� MyMultimap
    cout << "Original Multimap:\n";
    myMultimap.print();

    // ���Ҳ�ɾ����Ϊ1������Ԫ��
    myMultimap.erase(1);

    cout << "\nMultimap after erasing elements with key 1:\n";
    myMultimap.print();

    // ���Ҽ�Ϊ2��Ԫ��
    auto it = myMultimap.find(2);
    if (it != myMultimap.end()) {
        cout << "\nElement with key 2 found: " << it->second << endl;
    }
    else {
        cout << "\nElement with key 2 not found\n";
    }

    // ��ȡ������С
    cout << "\nSize of Multimap: " << myMultimap.size() << endl;

    // ��������Ƿ�Ϊ��
    cout << "Is Multimap empty? " << (myMultimap.empty() ? "Yes" : "No") << endl;

    // �������
    myMultimap.clear();
    cout << "\nMultimap after clearing:\n";
    myMultimap.print();

    // �����ض�����Ԫ������
    cout << "\nCount of elements with key 2: " << myMultimap.count(2) << endl;

    return 0;
}
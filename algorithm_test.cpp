#include <vector>
#include <iostream>
#include "algorithm.h"

int main()
{
    std::cout << "test min max: ";
    int n = 154554, m = 45648345;
    std::cout << mystd::min(n, m) << ' ' << mystd::max(n, m) << '\n';

    std::cout << "test gcd lcm: ";
    int p = 55, q = 500;
    std::cout << mystd::gcd(p, q) << ' ' << mystd::lcm(p, q) << '\n';

    std::cout << "test swap: ";
    int u = 359843, v = 458943799;
    std::cout << u << ' ' << v << '\n';
    mystd::swap(u, v);
    std::cout << u << ' ' << v << '\n';

    std::string s = "sdtguahsigh", t = "sdghuiersfds";
    std::cout << s << ' ' << t << '\n';
    mystd::swap(s, t);
    std::cout << s << ' ' << t << '\n';

    std::cout << "test iota: ";
    std::vector<int> iota_test(10, 0);
    mystd::iota(iota_test.begin(), iota_test.end(), 0);
    for (int i = 0; i < iota_test.size(); i++)
        std::cout << iota_test[i] << ' ';
    std::cout << '\n';

    std::cout << "test fill: ";
    std::vector<int> fill_test(10);
    mystd::fill(fill_test.begin(), fill_test.end(), 10);
    for (int i = 0; i < 10; i++)
        std::cout << fill_test[i] << ' ';
    std::cout << '\n';

    std::cout << "test find max_element minelement: ";
    std::vector<int> test(10);
    test = {11, 34, 2, 2, 453, 234, 4534, 436134, 154325, 13451243};
    std::cout << *mystd::find(test.begin(), test.end(), 2);
    std::cout << *mystd::max_element(test.begin(), test.end()) << ' ' << *mystd::min_element(test.begin(), test.end()) << '\n';

    std::cout << "test copy: ";
    std::vector<int> test2(10);
    mystd::copy(test.begin(), test.end(), test2.begin());
    for (int i = 0; i < 10; i++)
        std::cout << test2[i] << ' ';
    std::cout << '\n';

    std::cout << (mystd::is_sorted(test2.begin(), test2.end()) ? "test2 is sorted\n" : "test2 is not sorted\n");

    std::cout << "test count_if: ";
    std::cout << mystd::count_if(test.begin(), test.end(), 2) << '\n';

    std::cout << "test sort: ";
    mystd::sort(test.begin(), test.end());
    for(int i = 0; i < 10; i++)
        std::cout << test[i] << ' ';
    return 0;
}
#include <iostream>
#include <vector>
#include <memory>

int main(void)
{
    std::vector<int>    a;
    std::vector<int>    b;
    std::vector<int>    c(11, 1);

    // a.push_back(1);
    // b.push_back(1);
    // c.push_back(1);
    std::cout << "-----------------------origin-----------------------" << std::endl;
    std::cout << "a\t" << "size\t:" << a.size() << ", capacity\t: " << a.capacity() << std::endl;
    for (const auto &element : a)
        std::cout << element << " -> ";
    std::cout << "end" << std::endl;
    std::cout << "b\t" << "size\t:" << b.size() << ", capacity\t: " << b.capacity() << std::endl;
    for (const auto &element : b)
        std::cout << element << " -> ";
    std::cout << "end" << std::endl;
    std::cout << "c\t" << "size\t:" << c.size() << ", capacity\t: " << c.capacity() << std::endl;
    for (const auto &element : c)
        std::cout << element << " -> ";
    std::cout << "end" << std::endl;
    std::cout << "-----------------------operator overloading-----------------------" << std::endl;
    std::cout << "a == a\t: " << (a == a) << std::endl;
    std::cout << "a == b\t: " << (a == b) << std::endl;
    std::cout << "a == c\t: " << (a == c) << std::endl;
    std::cout << "a != a\t: " << (a != a) << std::endl;
    std::cout << "a != b\t: " << (a != b) << std::endl;
    std::cout << "a != c\t: " << (a != c) << std::endl;
    std::cout << "a < a\t: " << (a < a) << std::endl;
    std::cout << "a < b\t: " << (a < b) << std::endl;
    std::cout << "a < c\t: " << (a < c) << std::endl;
    std::cout << "a <= a\t: " << (a <= a) << std::endl;
    std::cout << "a <= b\t: " << (a <= b) << std::endl;
    std::cout << "a <= c\t: " << (a <= c) << std::endl;
    std::cout << "a > a\t: " << (a > a) << std::endl;
    std::cout << "a > b\t: " << (a > b) << std::endl;
    std::cout << "a > c\t: " << (a > c) << std::endl;
    std::cout << "a >= a\t: " << (a >= a) << std::endl;
    std::cout << "a >= b\t: " << (a >= b) << std::endl;
    std::cout << "a >= c\t: " << (a >= c) << std::endl;
    
    std::cout << "-----------------------swap-----------------------" << std::endl;
    swap(a, b);
    std::cout << "swap(a, b)" << std::endl;
    std::cout << "a\t" << "size\t:" << a.size() << ", capacity\t: " << a.capacity() << std::endl;
    for (const auto &element : a)
        std::cout << element << " -> ";
    std::cout << "end" << std::endl;
    std::cout << "b\t" << "size\t:" << b.size() << ", capacity\t: " << b.capacity() << std::endl;
    for (const auto &element : b)
        std::cout << element << " -> ";
    std::cout << "end" << std::endl;
    swap(a, c);
    std::cout << "swap(a, c)" << std::endl;
    std::cout << "a\t" << "size\t:" << a.size() << ", capacity\t: " << a.capacity() << std::endl;
    for (const auto &element : a)
        std::cout << element << " -> ";
    std::cout << "end" << std::endl;
    std::cout << "c\t" << "size\t:" << c.size() << ", capacity\t: " << c.capacity() << std::endl;
    for (const auto &element : c)
        std::cout << element << " -> ";
    std::cout << "end" << std::endl;
}

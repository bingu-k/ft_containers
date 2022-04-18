#include <iostream>
#include <vector>
#include <memory>

int main(void)
{
    std::vector<int>    a(5, 1);
    std::vector<int>    b(10, 2);


    std::cout << "a size\t: " << a.size() << ", a capacity\t: " << a.capacity() << std::endl;
    for (const auto& elem : a)
        std::cout << &elem << " -> ";
    std::cout << "end" << std::endl;
    std::cout << "b size\t: " << b.size() << ", b capacity\t: " << b.capacity() << std::endl;
    for (const auto& elem : b)
        std::cout << &elem << " -> ";
    std::cout << "end" << std::endl << std::endl;
    a.swap(b);
    std::cout << "a size\t: " << a.size() << ", a capacity\t: " << a.capacity() << std::endl;
    for (const auto& elem : a)
        std::cout << &elem << " -> ";
    std::cout << "end" << std::endl;
    std::cout << "b size\t: " << b.size() << ", b capacity\t: " << b.capacity() << std::endl;
    for (const auto& elem : b)
        std::cout << &elem << " -> ";
    std::cout << "end" << std::endl;
    return (0);
}
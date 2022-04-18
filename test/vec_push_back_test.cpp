#include <iostream>
#include <vector>

int main(void)
{
    std::vector<int>    a(4, 1);
    std::cout << "a\t" << "size\t:" << a.size() << ", capacity\t: " << a.capacity() << std::endl;
    for (const auto &element : a)
        std::cout << element << " -> ";
    std::cout << "end" << std::endl;
    a.push_back(2);
    a.push_back(2);
    a.push_back(2);
    std::cout << "Push Three Elements" << std::endl;
    std::cout << "a\t" << "size\t:" << a.size() << ", capacity\t: " << a.capacity() << std::endl;
    for (const auto &element : a)
        std::cout << element << " -> ";
    std::cout << "end" << std::endl;
    a.push_back(3);
    a.push_back(3);
    a.push_back(3);
    std::cout << "Push Three Elements" << std::endl;
    std::cout << "a\t" << "size\t:" << a.size() << ", capacity\t: " << a.capacity() << std::endl;
    for (const auto &element : a)
        std::cout << element << " -> ";
    std::cout << "end" << std::endl;
    
}
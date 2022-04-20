#include <iostream>
#include <vector>

void    printSize(std::vector<int> v, bool what)
{
    if (what == true)
    {
        std::cout << "size : " << v.size() << std::endl;
        std::cout << "capacity : " << v.capacity() << std::endl;
        for (const auto& e : v)
            std::cout << e << " -> ";
        std::cout << "end" << std::endl;
    }
}

void	is_empty(std::vector<int> const &vct)
{
	std::cout << "is_empty: " << vct.empty() << std::endl;
}

int main()
{
    {
        const int start_size = 7;
        std::vector<int> vct(start_size, 20);
        std::vector<int> vct2;
        std::vector<int>::iterator it = vct.begin();

        for (int i = 2; i < start_size; ++i)
            it[i] = (start_size - i) * 3;
        printSize(vct, true);

        vct.resize(10, 42);
        printSize(vct, true);

        vct.resize(18, 43);
        printSize(vct, true);
        vct.resize(10);
        printSize(vct, true);
        vct.resize(23, 44);
        printSize(vct, true);
        vct.resize(5);
        printSize(vct, true);
        vct.reserve(5);
        vct.reserve(3);
        printSize(vct, true);
        vct.resize(87);
        vct.resize(5);
        printSize(vct, true);

        is_empty(vct2);
        vct2 = vct;
        is_empty(vct2);
        vct.reserve(vct.capacity() + 1);
        printSize(vct, true);
        printSize(vct2, true);

        vct2.resize(0);
        is_empty(vct2);
        printSize(vct2, true);
    }
	return (0);
}
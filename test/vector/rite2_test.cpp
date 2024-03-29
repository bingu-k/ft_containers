#include "../../containers/vector.hpp"
#include <vector>
#include <iostream>

#define TESTED_TYPE int
#define TESTED_NAMESPACE ft

void    printSize(ft::vector<TESTED_TYPE> v, bool what)
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

void    printSize(std::vector<TESTED_TYPE> v, bool what)
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
int		main(void)
{
	const int size = 5;
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(size);
	TESTED_NAMESPACE::vector<TESTED_TYPE>::reverse_iterator it = vct.rbegin();
	TESTED_NAMESPACE::vector<TESTED_TYPE>::const_reverse_iterator ite = vct.rbegin();

	for (int i = 0; i < size; ++i)
	{
		std::cerr << (size - i) * 5 << std::endl;
		it[i] = (size - i) * 5;
		std::cerr << (it[i]) << std::endl;
	}
	it = it + 5;
	it = 1 + it;
	it = it - 4;
	std::cout << *(it += 2) << std::endl;
	std::cout << *(it -= 1) << std::endl;

	*(it -= 2) = 42;
	*(it += 2) = 21;

	std::cout << "const_ite +=/-=: " << *(ite += 2) << " | " << *(ite -= 2) << std::endl;

	std::cout << "(it == const_it): " << (ite == it) << std::endl;
	std::cout << "(const_ite - it): " << (ite - it) << std::endl;
	std::cout << "(ite + 3 == it): " << (ite + 3 == it) << std::endl;

	printSize(vct, true);
	return (0);
}

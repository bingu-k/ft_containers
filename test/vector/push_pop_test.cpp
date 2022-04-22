#include "../../containers/vector.hpp"
#include <vector>
#include <iostream>

#define TESTED_TYPE std::string
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
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(8);
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct2;
	TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it = vct.begin();

	for (unsigned long int i = 0; i < vct.size(); ++i)
		it[i] = std::string((vct.size() - i), i + 65);
	printSize(vct, true);

	std::cout << "push_back():\n" << std::endl;

	vct.push_back("One long string");
	vct2.push_back("Another long string");

	printSize(vct, true);
	printSize(vct2, true);

	vct.pop_back();
	vct2.pop_back();

	printSize(vct, true);
	printSize(vct2, true);

	return (0);
}
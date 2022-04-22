#include <iostream>
#include "../../containers/vector.hpp"
#include <vector>
#include <list>

#define TESTED_TYPE int
#define TESTED_NAMESPACE ft

void    printSize(std::vector<int>  &vec, std::string name)
{
    std::cout << name << ".size() : " << vec.size() << ",\t";
    std::cout << name << ".capacity() : " << vec.capacity() << std::endl;
    for (const auto& elem : vec)
        std::cout << elem << " -> ";
    std::cout << "end" << std::endl;
}

void    printSize(ft::vector<int>  &vec, std::string name)
{
    std::cout << name << ".size() : " << vec.size() << ",\t";
    std::cout << name << ".capacity() : " << vec.capacity() << std::endl;
    for (const auto& elem : vec)
        std::cout << elem << " -> ";
    std::cout << "end" << std::endl;
}

int		main(void)
{
	std::list<TESTED_TYPE> lst;
	std::list<TESTED_TYPE>::iterator lst_it;
	for (int i = 1; i < 5; ++i)
		lst.push_back(i * 3);

	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(lst.begin(), lst.end());
	printSize(vct, "vct");

	lst_it = lst.begin();
	for (int i = 1; lst_it != lst.end(); ++i)
		*lst_it++ = i * 5;
	vct.assign(lst.begin(), lst.end());
	printSize(vct, "vct");

	vct.insert(vct.end(), lst.rbegin(), lst.rend());
	printSize(vct, "vct");
	return (0);
}

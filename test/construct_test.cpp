#include <vector>
#include "../containers/vector.hpp"
#include <iostream>

#define TESTED_TYPE int

void    printSize(ft::vector<int> v)
{
	std::cout << "size : " << v.size() << std::endl;
	std::cout << "capacity : " << v.capacity() << std::endl;
	for (const auto& e : v)
		std::cout << e << " -> ";
	std::cout << "end" << std::endl;
}

void    printSize(std::vector<int> v)
{
	std::cout << "size : " << v.size() << std::endl;
	std::cout << "capacity : " << v.capacity() << std::endl;
	for (const auto& e : v)
		std::cout << e << " -> ";
	std::cout << "end" << std::endl;
}

int		main(void)
{
	ft::vector<TESTED_TYPE> vct(5);
	ft::vector<TESTED_TYPE>::iterator it = vct.begin(), ite = vct.end();

	std::cout << "len: " << (ite - it) << std::endl;
	for (; it != ite; ++it)
		*it = (ite - it);

	it = vct.begin();
	ft::vector<TESTED_TYPE> vct_range(it, --(--ite));
	for (int i = 0; it != ite; ++it)
		*it = ++i * 5;

	it = vct.begin();
	ft::vector<TESTED_TYPE> vct_copy(vct);
	for (int i = 0; it != ite; ++it)
		*it = ++i * 7;
	vct_copy.push_back(42);
	vct_copy.push_back(21);

	std::cout << "\t-- PART ONE --" << std::endl;
	printSize(vct);
	printSize(vct_range);
	printSize(vct_copy);

	vct = vct_copy;
	vct_copy = vct_range;
	vct_range.clear();

	std::cout << "\t-- PART TWO --" << std::endl;
	printSize(vct);
	printSize(vct_range);
	printSize(vct_copy);
	return (0);
}
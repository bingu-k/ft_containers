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
	ft::vector<TESTED_TYPE> vct(10);
	ft::vector<TESTED_TYPE> vct2;

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i) * 3;
	std::cout << "capacity()\t: " << vct.capacity() << std::endl;
	printSize(vct);

	vct2.insert(vct2.end(), 42);
	vct2.insert(vct2.begin(), 2, 21);
	std::cout << "capacity()\t: " << vct2.capacity() << std::endl;
	printSize(vct2);

	vct2.insert(vct2.end() - 2, 42);
	std::cout << "capacity()\t: " << vct2.capacity() << std::endl;
	printSize(vct2);

	vct2.insert(vct2.end(), 2, 84);
	std::cout << "capacity()\t: " << vct2.capacity() << std::endl;
	printSize(vct2);

	vct2.resize(4);
	std::cout << "capacity()\t: " << vct2.capacity() << std::endl;
	printSize(vct2);

	vct2.insert(vct2.begin() + 2, vct.begin(), vct.end());
	vct.clear();
	std::cout << "capacity()\t: " << vct2.capacity() << std::endl;
	printSize(vct2);

	std::cout << "capacity()\t: " << vct.capacity() << std::endl;
	printSize(vct);
	return (0);
}
#include <iostream>
#include <vector>
#include "../containers/vector.hpp"

int	main(void)
{
	std::vector<std::string> res;
	std::vector<std::string> res2;

	res.push_back(typeid(std::vector<int>::iterator::iterator_category).name());
	res.push_back(typeid(std::vector<int>::iterator::value_type).name());
	res.push_back(typeid(std::vector<int>::iterator::difference_type).name());
	res.push_back(typeid(std::vector<int>::iterator::iterator_type).name());
	res.push_back(typeid(std::vector<int>::iterator::pointer).name());
	res.push_back(typeid(std::vector<int>::iterator::reference).name());
	res.push_back(typeid(std::vector<int>::reverse_iterator::iterator_category).name());
	res.push_back(typeid(std::vector<int>::reverse_iterator::value_type).name());
	res.push_back(typeid(std::vector<int>::reverse_iterator::difference_type).name());
	res.push_back(typeid(std::vector<int>::reverse_iterator::pointer).name());
	res.push_back(typeid(std::vector<int>::reverse_iterator::reference).name());

	for (const auto& a : res)
		std::cout << a << "->";
	std::cout << "end" << std::endl;
	res2.push_back(typeid(ft::vector<int>::iterator::iterator_category).name());
	res2.push_back(typeid(ft::vector<int>::iterator::value_type).name());
	res2.push_back(typeid(ft::vector<int>::iterator::difference_type).name());
	res2.push_back(typeid(ft::vector<int>::iterator::iterator_type).name());
	res2.push_back(typeid(ft::vector<int>::iterator::pointer).name());
	res2.push_back(typeid(ft::vector<int>::iterator::reference).name());
	res2.push_back(typeid(ft::vector<int>::reverse_iterator::iterator_category).name());
	res2.push_back(typeid(ft::vector<int>::reverse_iterator::value_type).name());
	res2.push_back(typeid(ft::vector<int>::reverse_iterator::difference_type).name());
	res2.push_back(typeid(ft::vector<int>::reverse_iterator::pointer).name());
	res2.push_back(typeid(ft::vector<int>::reverse_iterator::reference).name());

	for (const auto& a : res2)
		std::cout << a << "->";
	std::cout << "end" << std::endl;
	return (0);
}
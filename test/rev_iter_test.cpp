#include <iostream>
#include <vector>
#include "../containers/vector.hpp"

int main(void)
{
	std::vector<int> v1;

	for (int i = 1; i < 5; i++)
		v1.push_back(i);
	for (const auto& e : v1)
		std::cout << e << " -> ";
	std::cout << "end" << std::endl;
	std::cout << "rbegin()\t: " << *(v1.rbegin()) << std::endl;
	std::cout << "rend()\t: " << *(v1.rend()) << std::endl;
	std::cout << "==============================================\n";
	ft::vector<int> v2;

	for (int i = 1; i < 5; i++)
		v2.push_back(i);
	for (const auto& e : v2)
		std::cout << e << " -> ";
	std::cout << "end" << std::endl;
	std::cout << "rbegin()\t: " << (*(v2.rbegin())) << std::endl;
	std::cout << "rend()\t: " << (*(v2.rend())) << std::endl;
	return(0);
}
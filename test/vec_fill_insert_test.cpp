#include <iostream>
#include <vector>
#include "../containers/vector.hpp"

template <typename T>
std::vector<int> insert_test_2(std::vector<T> vector) {
    std::vector<int> v;
    vector.assign(1000, 1);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    vector.insert(vector.end() - 50, 4200 * 10000 , 2);
    v.push_back(vector[2121]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
	std::cerr << "\nstd\t";
	for (const auto& a : v)
		std::cerr << a << " -> ";
	std::cerr << "end" << std::endl;
    return v;
}

template <typename T>
std::vector<int> insert_test_2(ft::vector<T> vector) {
    std::vector<int> v;
    vector.assign(1000, 1);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    vector.insert(vector.end() - 50, 4200 * 10000 , 2);
    v.push_back(vector[2121]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
	std::cerr << "\nft\t";
	for (const auto& a : v)
		std::cerr << a << " -> ";
	std::cerr << "end" << std::endl;
    return v;
}

int	main(void)
{
	std::vector<int>	v;
	ft::vector<int>		b;

	insert_test_2(v);
	insert_test_2(b);
	return (0);
}
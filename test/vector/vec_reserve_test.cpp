#include <vector>
#include "../containers/vector.hpp"
#include <iostream>

int	main(void)
{
	std::vector<int> v;
	ft::vector<int>	b;
	std::vector<int> res;
	std::vector<int> res_b;
	
	int	_ratio(10000);

    v.assign(9900 * _ratio, 1);
    v.resize(5000 * _ratio);
    v.reserve(5000 * _ratio);
	res.push_back(v.size());
	res.push_back(v.capacity());
    v.resize(7000 * _ratio);
	res.push_back(v.size());
	res.push_back(v.capacity());
    v.resize(15300 * _ratio, int());
	res.push_back(v.size());
	res.push_back(v.capacity());
	std::cerr << "\nstd\tratio\t: " << _ratio << "\t";
	for (const auto& a : res)
		std::cerr << a << " -> ";
	std::cerr << "end" << std::endl;

	b.assign(9900 * _ratio, 1);
    b.resize(5000 * _ratio);
    b.reserve(5000 * _ratio);
	res_b.push_back(b.size());
	res_b.push_back(b.capacity());
    b.resize(7000 * _ratio);
	res_b.push_back(b.size());
	res_b.push_back(b.capacity());
    b.resize(15300 * _ratio, int());
	res_b.push_back(b.size());
	res_b.push_back(b.capacity());
	std::cerr << "ft\tratio\t: " << _ratio << "\t";
	for (const auto& a : res_b)
		std::cerr << a << " -> ";
	std::cerr << "end" << std::endl;
}
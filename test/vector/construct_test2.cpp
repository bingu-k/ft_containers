#include <vector>
#include "../../containers/vector.hpp"
#include <iostream>

#define _vector ft::vector

template <typename T>
std::vector<int> constructor_test(std::vector<T> vector, int _ratio) {
    std::vector<int> v;
    std::vector<int> tmp0(vector);
    std::vector<int> tmp(1000 * _ratio, 4), tmp2(1000 * _ratio, 5);
    tmp = tmp2;
    std::vector<int> tmp3(tmp);
    std::vector<int> tmp4(tmp.begin(), tmp.end());
    v.push_back(tmp4.size());
    v.push_back(tmp4.capacity());
    v.push_back(tmp[2]);
    v.push_back(tmp3[2]);
    v.push_back(tmp4[2]);
    try { std::vector<int> tmp5(-1, -1); }
    catch (std::exception &e) { v.push_back(1); }
    return v;
}

template <typename T>
std::vector<int> constructor_test(_vector<T> vector, int _ratio) {
    std::vector<int> v;
	_vector<int> tmp0(vector);
    _vector<int> tmp(1000 * _ratio, 4), tmp2(1000 * _ratio, 5);
    tmp = tmp2;
    _vector<int> tmp3(tmp);
    _vector<int> tmp4(tmp.begin(), tmp.end());
    v.push_back(tmp4.size());
    v.push_back(tmp4.capacity());
    v.push_back(tmp[2]);
    v.push_back(tmp3[2]);
    v.push_back(tmp4[2]);
    try { _vector<int> tmp5(-1, -1); }
    catch (std::exception &e) { v.push_back(1); }
    return v;
}

int	main(void)
{
	std::vector<int>	v1;
	ft::vector<int>		v2;
	std::vector<int>	res1 = constructor_test(v1, 1000);
	std::vector<int>	res2 = constructor_test(v2, 1000);
	std::cout << "res1\tsize\t: " << res1.size() << std::endl;
	std::cout << "res1\tcapacity\t: " << res1.capacity() << std::endl;
	for (const auto a : res1)
		std::cout << a << " -> ";
	std::cout << "end" << std::endl;
	std::cout << "\nres2\tsize\t: " << res2.size() << std::endl;
	std::cout << "res2\tcapacity\t: " << res2.capacity() << std::endl;
	for (const auto a : res2)
		std::cout << a << " -> ";
	std::cout << "end" << std::endl;
	return (0);
}
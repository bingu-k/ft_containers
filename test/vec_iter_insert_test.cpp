#include <iostream>
#include <vector>
#include "../containers/vector.hpp"
#include <memory>

template <typename T>
std::vector<int> insert_test_3(std::vector<T> vector, int _ratio) {
    std::vector<int> v;
    std::vector<int> tmp;
    tmp.assign(2600 * _ratio, 1);
    vector.assign(4200 * _ratio, 1);
    vector.insert(vector.end() - 1000 * _ratio, tmp.begin(), tmp.end());
    v.push_back(vector[3]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());

    std::vector<std::string> vv;
    std::vector<std::string> v1;
    std::string	k2("hello");
    std::string	k3("world");
    std::string	k4("ohhhhh");

    v1.push_back(k2);
    v1.push_back(k3);
    v1.push_back(k4);
    try { vv.insert(vv.begin(), v1.begin(), v1.end()); }
    catch (...) {
        v.push_back(vv.size());
        v.push_back(vv.capacity());
    }

    return v;
}

template <typename T>
std::vector<int> insert_test_3(ft::vector<T> vector, int _ratio) {
    std::vector<int> v;
    ft::vector<int> tmp;
    tmp.assign(2600 * _ratio, 1);
    vector.assign(4200 * _ratio, 1);
    vector.insert(vector.end() - 1000 * _ratio, tmp.begin(), tmp.end());
    v.push_back(vector[3]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());

    ft::vector<std::string> vv;
    ft::vector<std::string> v1;
    std::string	k2("hello");
    std::string	k3("world");
    std::string	k4("ohhhhh");

    v1.push_back(k2);
    v1.push_back(k3);
    v1.push_back(k4);
    try { vv.insert(vv.begin(), v1.begin(), v1.end()); }
    catch (...) {
        v.push_back(vv.size());
        v.push_back(vv.capacity());
    }

    return v;
}

int main()
{
	ft::vector<int>		vec_;
	std::vector<int>	vec;
	for (int i = 1; i < 6; i++)
	{
		std::vector<int>	res_ = insert_test_3(vec_, i);
		std::vector<int>	res = insert_test_3(vec, i);

		for (const auto& a : res_)
				std::cout << a << " -> ";
			std::cout << "end" << std::endl;
		for (const auto& a : res)
				std::cout << a << " -> ";
			std::cout << "end" << std::endl;
	}
	return (0);
}
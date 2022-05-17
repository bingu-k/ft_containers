#include <iostream>
#include <vector>
#include "../../containers/vector.hpp"
#include <time.h>

#define TEST_NAME	std

template <typename T>
static void print_vector(T vec, std::string type)
{
	typename T::iterator it;

	std::cout << BOLD << type << ", size: " << vec.size() << ", empty: " << vec.empty() << ", capacity: " << vec.capacity() << RESET << std::endl;
	it = vec.begin();
	while (it != vec.end())
	{
		std::cout << *it;
		if (it + 1 != vec.end())
			std::cout << " - ";
		++it;
	}
	std::cout << std::endl;
}

template <typename T>
static void print_vector_reverse(T vec, std::string type)
{
	typename T::iterator it;

	std::cout << BOLD << type << ", size: " << vec.size() << ", empty: " << vec.empty() << ", capacity: " << vec.capacity() << RESET << std::endl;
	it = vec.rbegin();
	while (it != vec.rend())
	{
		std::cout << *it;
		if (it + 1 != vec.rend())
			std::cout << " - ";
		++it;
	}
	std::cout << std::endl;
}

static void default_constructor(void)
{
	ft::vector<int> v1;
	std::vector<int> v2;
	check("v1 == v2", v1 == v2);
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v2.push_back(1);
	v2.push_back(2);
	v2.push_back(3);
	check("v1 == v2", v1 == v2);
}

static void copy_constructor(void)
{
	ft::vector<int> v1;
	std::vector<int> v2;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v2.push_back(1);
	v2.push_back(2);
	v2.push_back(3);
	ft::vector<int> v3(v1);
	std::vector<int> v4(v2);
	v1.push_back(42);
	v2.push_back(42);
	check("v1 == v2", (v1 == v2));
	check("v3 == v4", (v3 == v4));
	check("v1 != v3", (v1 != v3));
	check("v2 != v4", (v2 != v4));
}

static void max_size(void)
{
	ft::vector<std::string> v1;
	std::vector<std::string> v2;
	check("v1.max_size() == v2.max_size()", v1.max_size(), v2.max_size());
	v1.push_back("test");
	v2.push_back("test");
	check("v1.max_size() == v2.max_size()", v1.max_size(), v2.max_size());
}

static void resize(void)
{
	ft::vector<std::string> v1;
	std::vector<std::string> v2;
	v1.resize(10, "test");
	v2.resize(10, "test");
	check("v1 == v2", (v1 == v2));
	v1.resize(2, "42");
	v2.resize(2, "42");
	check("v1 == v2", (v1 == v2));
}

static void access_operator(void)
{
	ft::vector<int> v1;
	std::vector<int> v2;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v2.push_back(1);
	v2.push_back(2);
	v2.push_back(3);
	check("v1[0] == v2[0]", v1[0], v2[0]);
	check("v1[1] == v2[1]", v1[1], v2[1]);
	check("v1[2] == v2[2]", v1[2], v2[2]);
	try
	{
		std::cout << "v1.at(100): " << v1.at(100) << ": " << FAIL << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << ": " << std::string(7, ' ') << BOLD << GREEN << GOOD << RESET << std::endl;
	}
	try
	{
		std::cout << "v2.at(100): " << v2.at(100) << ": " << FAIL  << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << ": " << std::string(20, ' ') << BOLD << GREEN << GOOD << RESET << std::endl;
	}
	try
	{
		std::cout << "v1.at(-1): " << v1.at(-1) << ": " << FAIL  << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << ": " << std::string(8, ' ') << BOLD << GREEN << GOOD << RESET << std::endl;
	}
	try
	{
		std::cout << "v2.at(-1): " << v2.at(-1) << ": " << FAIL  << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << ": " << std::string(21, ' ') << BOLD << GREEN << GOOD << RESET << std::endl;
	}
}

static void front_back(void)
{
	ft::vector<int> v1;
	std::vector<int> v2;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v2.push_back(1);
	v2.push_back(2);
	v2.push_back(3);
	check("v1.front() == v2.front()", v1.front(), v2.front());
	check("v1.back() == v2.back()", v1.front(), v2.front());
}

static void assign(void)
{
	std::string test[] = {"Hey", "what's", "up", "?"};
	ft::vector<std::string> v1;
	std::vector<std::string> v2;
	v1.assign(test, test + 4);
	v2.assign(test, test + 4);
	check("v1 == v2", v1 == v2);
	v1.assign(10, "?");
	v2.assign(10, "?");
	check("v1 == v2", v1 == v2);
}

static void insert(void)
{
	int test[] = {1, 2, 3};
	ft::vector<int> v1;
	std::vector<int> v2;
	v1.insert(v1.begin(), 42);
	v1.insert(v1.end(), 21);
	v1.insert(v1.begin(), 10);
	v1.insert(v1.begin() + 1, 11);
	v1.insert(v1.begin() + 2, (size_t)3, 0);
	v1.insert(v1.begin() + 1, test, test + 3);
	v2.insert(v2.begin(), 42);
	v2.insert(v2.end(), 21);
	v2.insert(v2.begin(), 10);
	v2.insert(v2.begin() + 1, 11);
	v2.insert(v2.begin() + 2, (size_t)3, 0);
	v2.insert(v2.begin() + 1, test, test + 3);
	check("v1 == v2", v1 == v2);
}

static void erase(void)
{
	std::string test[] = {"Hey", "what's", "up", "?"};
	ft::vector<std::string> v1;
	std::vector<std::string> v2;
	v1.assign(test, test + 4);
	v2.assign(test, test + 4);
	v1.erase(v1.begin() + 2);
	v2.erase(v2.begin() + 2);
	check("v1 == v2", v1 == v2);
	v1.clear();
	v2.clear();
	check("v1 == v2", v1 == v2);
}

static void swap(void)
{
	ft::vector<int> v1;
	std::vector<int> v2;
	ft::vector<int> v3;
	std::vector<int> v4;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v2.push_back(1);
	v2.push_back(2);
	v2.push_back(3);
	v3.push_back(42);
	v3.push_back(43);
	v4.push_back(42);
	v4.push_back(43);
	v1.swap(v3);
	v2.swap(v4);
	check("v1 == v2", v1 == v2);
	check("v3 == v4", v3 == v4);
}

static void operators(void)
{
	ft::vector<int> v1;
	std::vector<int> v2;
	ft::vector<int> v3;
	std::vector<int> v4;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v2.push_back(1);
	v2.push_back(2);
	v2.push_back(3);
	v3 = v1;
	v4 = v2;
	check("v1 == v2", (v1 == v3), (v2 == v4));
	check("v1 != v2", (v1 != v3), (v2 != v4));
	check("v1 > v2", (v1 > v3), (v2 > v4));
	check("v1 < v2", (v1 < v3), (v2 < v4));
	check("v1 >= v2", (v1 >= v3), (v2 >= v4));
	check("v1 <= v2", (v1 <= v3), (v2 <= v4));
	v1.push_back(42);
	v2.push_back(42);
	check("v1 == v2", (v1 == v3), (v2 == v4));
	check("v1 != v2", (v1 != v3), (v2 != v4));
	check("v1 > v2", (v1 > v3), (v2 > v4));
	check("v1 < v2", (v1 < v3), (v2 < v4));
	check("v1 >= v2", (v1 >= v3), (v2 >= v4));
	check("v1 <= v2", (v1 <= v3), (v2 <= v4));
	v3.push_back(43);
	v4.push_back(43);
	check("v1 == v2", (v1 == v3), (v2 == v4));
	check("v1 != v2", (v1 != v3), (v2 != v4));
	check("v1 > v2", (v1 > v3), (v2 > v4));
	check("v1 < v2", (v1 < v3), (v2 < v4));
	check("v1 >= v2", (v1 >= v3), (v2 >= v4));
	check("v1 <= v2", (v1 <= v3), (v2 <= v4));
}

void	main(void)
{
	clock_t	start = clock();

	default_constructor();
	copy_constructor();
	max_size();
	resize();
	access_operator();
	front_back();
	assign();
	insert();
	erase();
	swap();
	operators();
	clock_t	end = clock();
	double	result = static_cast<double>(end - start);
	std::cout << "Total Time\t: " << result << " ms" << std::endl;
	return (0);
}
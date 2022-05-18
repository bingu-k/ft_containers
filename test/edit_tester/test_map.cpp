#include "tester.hpp"
#include <utility>
#include <time.h>

#define TEST_NAME	std

template <class T>
static void print_map(T &map)
{
	typename T::iterator it = map.begin();
	std::cout << " --- map of size " << map.size() << " ---" << std::endl;
	while (it != map.end())
	{
		std::cout << it->first << ": " << it->second << std::endl;
		++it;
	}
	std::cout << " --- " << std::endl;
}

static void constructors(void)
{
	print_header("Constructors / Copy");
	TEST_NAME::pair<int, int> a[] = {TEST_NAME::make_pair(0, 1), TEST_NAME::make_pair(1, 0), TEST_NAME::make_pair(2, 1)};
	TEST_NAME::map<int, int> m1;
	TEST_NAME::map<int, int> m2;
	check("(default) m1 == m2", (m1 == m2));
	TEST_NAME::map<int, int> m3(a, a + 3);
	TEST_NAME::map<int, int> m4(a, a + 3);
	check("(range) m3 == m4", (m3 == m4));
	TEST_NAME::map<int, int> m5(m3);
	TEST_NAME::map<int, int> m6(m4);
	check("(copy) m5 == m6", (m3 == m4));
	TEST_NAME::map<int, int> m7;
	TEST_NAME::map<int, int> m8;
	m7[0] = 1;
	m7[1] = 2;
	m7[2] = 3;
	m8[0] = 1;
	m8[1] = 2;
	m8[2] = 3;
	// print_map(m7);
	// print_map(m8);
	// std::cout << (++m7.begin())->second << std::endl;
	// ft::map<int, int>::iterator it = m7.begin();
	// while (it != m7.end())
	// {
	// 	// ft::map<int, int>::iterator it2 = m7.find(it->first);
	// 	std::cout << it.node()->pair.second << std::endl;
	// 	// std::cout << it->first << "=" << it2->second << std::endl;
	// 	++it;
	// }
	check("(copy) m7 == m8", (m7 == m8));
	TEST_NAME::map<int, int> m9;
	TEST_NAME::map<int, int> m10;
	m9 = m7;
	m10 = m8;
	check("(copy) m9 == m10", (m9 == m10));
}

static void max_size(void)
{
	print_header("Size");
	TEST_NAME::map<int, int> m1;
	TEST_NAME::map<int, int> m2;
	check("m1.max_size() == m2.max_size()", m1.max_size(), m2.max_size());
	TEST_NAME::map<std::string, int> m3;
	TEST_NAME::map<std::string, int> m4;
	check("m3.max_size() == m4.max_size()", m3.max_size(), m4.max_size());
}

static void access_operator(void)
{
	print_header("[] operator");
	TEST_NAME::map<std::string, int> m1;
	TEST_NAME::map<std::string, int> m2;
	m1["a"] = 1;
	m1["b"] = 0;
	m1["c"] = 42;
	m1["d"] = -5;
	m1["d"] = 11;
	m1["test"] = 100;
	m2["a"] = 1;
	m2["b"] = 0;
	m2["c"] = 42;
	m2["d"] = -5;
	m2["d"] = 11;
	m2["test"] = 100;
	check("m1 == m2", m1 == m2);
	check("m1['a'] == m2['a']", m1["a"], m2["a"]);
	check("m1['d'] == m2['d']", m1["d"], m2["d"]);
	check("m1['test'] == m2['test']", m1["test"], m2["test"]);
	check("m1['z'] == m2['z']", m1["z"], m2["z"]);
}

static void insert(void)
{
	print_header("Insert");
	TEST_NAME::pair<int, int> a[] = {TEST_NAME::make_pair(0, 1), TEST_NAME::make_pair(1, 0), TEST_NAME::make_pair(2, 1)};
	TEST_NAME::map<int, int> m1(a, a + 3);
	TEST_NAME::map<int, int> m2(a, a + 3);
	m1.insert(++m1.begin(), TEST_NAME::make_pair(5, 5));
	m2.insert(++m2.begin(), TEST_NAME::make_pair(5, 5));
	check("m1 == m2", m1 == m2);
	m1.insert(TEST_NAME::make_pair(5, 0));
	m2.insert(TEST_NAME::make_pair(5, 0));
	m1.insert(TEST_NAME::make_pair(10, 54));
	m2.insert(TEST_NAME::make_pair(10, 54));
	check("m1 == m2", m1 == m2);
}

static void erase(void)
{
	print_header("Erase");
	TEST_NAME::map<std::string, int> m1;
	TEST_NAME::map<std::string, int> m2;
	m1["test"] = 1;
	m1["a"] = 2;
	m1["b"] = 3;
	m1["c"] = 4;
	m1["d"] = 6;
	m1["e"] = 8;
	m2["test"] = 1;
	m2["a"] = 2;
	m2["b"] = 3;
	m2["c"] = 4;
	m2["d"] = 6;
	m2["e"] = 8;
	check("m1 == m2", m1 == m2);
	m1.erase(++m1.begin());
	m2.erase(++m2.begin());
	check("m1 == m2", m1 == m2);
	m1.erase(++m1.begin(), --m1.end());
	m2.erase(++m2.begin(), --m2.end());
	check("m1 == m2", m1 == m2);
	m1.erase("a");
	m2.erase("a");
	check("m1 == m2", m1 == m2);
}

static void swap(void)
{
	print_header("Swap");
	TEST_NAME::map<std::string, int> m1;
	TEST_NAME::map<std::string, int> m2;
	TEST_NAME::map<std::string, int> m3;
	TEST_NAME::map<std::string, int> m4;
	m1["a"] = 1;
	m1["b"] = 2;
	m1["c"] = 3;
	m2["a"] = 1;
	m2["b"] = 2;
	m2["c"] = 3;
	m3["a"] = 42;
	m3["b"] = 21;
	m4["a"] = 42;
	m4["b"] = 21;
	m1.swap(m3);
	m2.swap(m4);
	check("m1 == m2", m1 == m2);
	check("m3 == m4", m3 == m4);
}

static void clear(void)
{
	print_header("Clear");
	TEST_NAME::map<std::string, int> m1;
	TEST_NAME::map<std::string, int> m2;
	m1["a"] = 1;
	m1["b"] = 42;
	m2["a"] = 1;
	m2["b"] = 42;
	m1.clear();
	m2.clear();
	check("m1 == m2", m1 == m2);
}

static void find(void)
{
	print_header("Find");
	TEST_NAME::map<std::string, int> m1;
	TEST_NAME::map<std::string, int> m2;
	m1["a"] = 1;
	m1["b"] = 42;
	m2["a"] = 1;
	m2["b"] = 42;
	check("m1.find('a') == m2.find('a')", m1.find("a")->second, m2.find("a")->second);
	check("m1.find('z') == m2.find('z')", m1.find("a")->second, m2.find("a")->second);
}

static void count(void)
{
	print_header("Count");
	TEST_NAME::map<std::string, int> m1;
	TEST_NAME::map<std::string, int> m2;
	m1["a"] = 1;
	m1["b"] = 42;
	m1["b"] = 21;
	m2["a"] = 1;
	m2["b"] = 42;
	m2["b"] = 21;
	check("m1.count('a') == m2.count('a')", m1.count("a"), m2.count("a"));
	check("m1.count('b') == m2.count('b')", m1.count("b"), m2.count("b"));
	check("m1.count('z') == m2.count('z')", m1.count("z"), m2.count("z"));
}

static void bounds()
{
	print_header("Bounds");
	TEST_NAME::map<std::string, int> m1;
	TEST_NAME::map<std::string, int> m2;
	m1["a"] = 1;
	m1["b"] = 42;
	m1["c"] = 42;
	m1["d"] = 42;
	m2["a"] = 1;
	m2["b"] = 42;
	m2["c"] = 42;
	m2["d"] = 42;
	check("m1.lower_bound() == m2.lower_bound()", m1.lower_bound("a")->first, m2.lower_bound("a")->first);
	check("m1.lower_bound() == m2.lower_bound()", m1.lower_bound("c")->first, m2.lower_bound("c")->first);
	check("m1.upper_bound() == m2.upper_bound()", m1.upper_bound("a")->first, m2.upper_bound("a")->first);
	check("m1.upper_bound() == m2.upper_bound()", m1.upper_bound("c")->first, m2.upper_bound("c")->first);
}

static void range(void)
{
	print_header("Equal range");
	TEST_NAME::map<std::string, int> m1;
	TEST_NAME::map<std::string, int> m2;
	m1["a"] = 1;
	m1["b"] = 42;
	m1["c"] = 42;
	m1["d"] = 42;
	m2["a"] = 1;
	m2["b"] = 42;
	m2["c"] = 42;
	m2["d"] = 42;
	TEST_NAME::pair<TEST_NAME::map<std::string, int>::iterator, TEST_NAME::map<std::string, int>::iterator> a = m1.equal_range("a");
	TEST_NAME::pair<TEST_NAME::map<std::string, int>::iterator, TEST_NAME::map<std::string, int>::iterator> b = m2.equal_range("a");
	check("a.first->first == b.first->first", a.first->first, b.first->first);
	check("a.first->second == b.first->second", a.first->second, b.first->second);
	check("a.second->first == b.second->first", a.second->first, b.second->first);
	check("a.second->second == b.second->second", a.second->second, b.second->second);
}

static void operators_comp(void)
{
	print_header("Operators");
	TEST_NAME::map<std::string, int> m1;
	TEST_NAME::map<std::string, int> m2;
	m1["a"] = 1;
	m1["b"] = 42;
	m1["c"] = 42;
	m1["d"] = 42;
	m2["a"] = 1;
	m2["b"] = 42;
	m2["c"] = 42;
	m2["d"] = 42;
	TEST_NAME::map<std::string, int> m3;
	TEST_NAME::map<std::string, int> m4;
	m3 = m1;
	m4 = m2;
	check("m1 == m2", (m1 == m3), (m2 == m4));
	check("m1 != m2", (m1 != m3), (m2 != m4));
	check("m1 > m2", (m1 > m3), (m2 > m4));
	check("m1 < m2", (m1 < m3), (m2 < m4));
	check("m1 >= m2", (m1 >= m3), (m2 >= m4));
	check("m1 <= m2", (m1 <= m3), (m2 <= m4));
	m1["e"] = 1;
	m2["e"] = 1;
	check("m1 == m2", (m1 == m3), (m2 == m4));
	check("m1 != m2", (m1 != m3), (m2 != m4));
	check("m1 > m2", (m1 > m3), (m2 > m4));
	check("m1 < m2", (m1 < m3), (m2 < m4));
	check("m1 >= m2", (m1 >= m3), (m2 >= m4));
	check("m1 <= m2", (m1 <= m3), (m2 <= m4));
	m3["e"] = 3;
	m4["e"] = 3;
	check("m1 == m2", (m1 == m3), (m2 == m4));
	check("m1 != m2", (m1 != m3), (m2 != m4));
	check("m1 > m2", (m1 > m3), (m2 > m4));
	check("m1 < m2", (m1 < m3), (m2 < m4));
	check("m1 >= m2", (m1 >= m3), (m2 >= m4));
	check("m1 <= m2", (m1 <= m3), (m2 <= m4));
}

int	main(void)
{
	clock_t	start = clock();
	print_header("map");
	constructors();
	max_size();
	access_operator();
	insert();
	erase();
	swap();
	clear();
	find();
	count();
	bounds();
	range();
	operators_comp();
	clock_t end = clock();
	double	result = static_cast<double>(end - start);
	std::cout << "Total time\t: " << result << " ms" << std::endl;
	system("leaks a.out");
	return(0);
}
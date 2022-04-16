#include <iterator>
#include <vector>
#include <memory>
#include <list>
#include <forward_list>
#include <iostream>
#include <cstddef>
#include <type_traits>
#include <__config>
#include <algorithm>

int	main()
{
	// std::vector<int>	a;
	// try
	// {
	// 	std::forward_list<int> iit;
	// 	iit.push_front(1);
	// 	iit.push_front(2);
	// 	iit.push_front(3);
	// 	std::list<int>	lst;
	// 	lst.push_back(1);
	// 	lst.push_back(2);
	// 	lst.push_back(3);

	// 	std::forward_list<int>::iterator it1(iit.begin());
	// 	std::forward_list<int>::iterator it2(iit.end());
	// 	std::vector<int> a1(it1, it2);
	// 	std::vector<int>::iterator	i1(a1.begin());
	// 	for (; i1 != a1.end(); i1++)
	// 		std::cout << *i1 << std::endl;
	// }
	// catch(const std::exception& e)
	// {
	// 	std::cerr << e.what() << '\n';
	// }
	
	// std::cout << "success" << std::endl;
	// try
	// {
	// 	std::istream_iterator<int> eos;              // end-of-stream iterator
	// 	std::istream_iterator<int> it1 (std::cin);   // stdin iterator

	// 	std::cout << "here?" << std::endl;
	// 	std::istream_iterator<int> copy_it(it1);
	// 	// std::istream_iterator<int> it2 ();   // stdin iterator

	// 	std::cout << "here?" << std::endl;
	// 	std::vector<int> a1(copy_it, ++copy_it);
	// 	std::cout << "here?" << std::endl;
	// 	std::vector<int>::iterator	i1(a1.begin());
	// 	for (; i1 != a1.end(); i1++)
	// 		std::cout << *i1 << std::endl;
	// }
	// catch(const std::exception& e)
	// {
	// 	std::cerr << e.what() << '\n';
	// }

	// std::cout << "success" << std::endl;
	{
		// std::vector<int>	a;
		// std::vector<int>	b;
		// std::vector<int>	c;
		// std::vector<int>	d;
		// int					temp(1);
		// a.push_back(1);
		// b.push_back(2);

		// // a++;
		// // ++a;
		// // a--;
		// // --a;
		// // std::cout << "a : " << a << "\tb : " << b << std::endl;
		// std::cout << "(a < b) : " << (a < b) << std::endl;
		// std::cout << "(a > b) : " << (a > b) << std::endl;
		// std::cout << "(a <= b) : " << (a <= b) << std::endl;
		// std::cout << "(a >= b) : " << (a >= b) << std::endl;
		// std::cout << "(a == b) : " << (a == b) << std::endl;
		// std::cout << "(a != b) : " << (a != b) << std::endl;
		// // a += temp;
		// // std::cout << "(a += 1) : " << a << std::endl;
		// // a -= temp;
		// // std::cout << "(a -= 1) : " << a << std::endl;
		// // c = a + temp;
		// // d = a - temp;
	}

	// std::vector<int>	a;
	// std::vector<int>	copy_a(a);
	// std::vector<int>	b(15, 1);
	// a.push_back(1);
	// for (int i = 1; i < 11; i++)
	// 	a.push_back(i * 10);
	{
		// std::vector<std::string>	a;
		// a.push_back("what");
		// a.push_back("is");
		// a.push_back("love");
	}
	{
		// std::cout << "a.size()\t: " << a.size() << std::endl;
		// std::cout << "b.size()\t: " << b.size() << std::endl;
		// std::cout << "a.begin()\t: " << *(a.begin()) << std::endl;
		// std::cout << "b.begin()\t: " << *(b.begin()) << std::endl;
		// std::cout << "a.begin()\t: " << *(a.begin()) << std::endl;
		// std::cout << "b.end()\t: " << *(b.end()) << std::endl;
		// std::cout << "a.end() - a.begin()\t: " << (a.end() - a.begin()) << std::endl;
		// std::cout << "b.end() - b.begin()\t: " << (b.end() - b.begin()) << std::endl;
	}
	{
		// std::cout << "a.max_size()\t: " << a.max_size() << std::endl;
		// std::cout << "a.get_allocator().max_size()\t: " << a.get_allocator().max_size() << std::endl;
	}
	/*{
		std::cout << "a.capacity()\t: " << a.capacity() << std::endl;
		std::cout << "b.capacity()\t: " << b.capacity() << std::endl;
	}
	{
		std::cout << "a.empty()\t: " << a.empty() << std::endl;
		try
		{
			// a.reserve(-1);
			// std::cout << a.at(4611686018427387904) << std::endl;
			std::cout << a.max_size() << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		};
		
		for (int i = 1; i < 5; i++)
			a.push_back(i * 10);
		for (const auto &element : a)
			std::cout << element << " -> ";
		std::cout << "end" << std::endl;
		std::cout << "capacity\t: " << a.capacity() << std::endl;
		a.assign(10, 1);
		std::cout << "a.assign(10, 1)\t, capacity\t: " << a.capacity() << std::endl;
		for (const auto &element : a)
			std::cout << element << " -> ";
		std::cout << "end" << std::endl;
		try
		{
			// a.assign(-1, 2);
			// a.assign(4611686018427387904, 3);
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
		
		a.assign(5, 2);
		std::cout << "a.assign(5, 2), capacity\t: " << a.capacity() << std::endl;
		for (const auto &element : a)
			std::cout << element << " -> ";
		std::cout << "end" << std::endl;
		for (int i = 0; i < 2; i++)
			std::cout << i << std::endl;
	}*/
	// {
	// 	for (int i = 1; i < 11; i++)
	// 		a.push_back(i * 10);
	// 	std::cout << "capacity\t: " << b.capacity() << std::endl;
	// 	for (const auto &element : b)
	// 		std::cout << element << " -> ";
	// 	std::cout << "end" << std::endl;
	// 	std::vector<int>::iterator	first = a.begin();
	// 	std::vector<int>::iterator	last = a.end();
	// 	std::cout << "b.assign(a.begin, a.end)" << std::endl;
	// 	b.assign(first, last);
	// 	std::cout << "capacity\t: " << b.capacity() << std::endl;
	// 	for (const auto &element : b)
	// 		std::cout << element << " -> ";
	// 	std::cout << "end" << std::endl;
	// }
	/*{
		std::vector<int>	a;
		std::vector<int>	b(15, 1);
		std::cout << "capacity\t: " << a.capacity() << std::endl;
		a.resize(0);
		std::cout << "capacity\t: " << a.capacity() << std::endl;
		std::cout << "size\t:" << b.size() << ", capacity\t: " << b.capacity() << std::endl;
		b.push_back(1);
		std::cout << "size\t:" << b.size() << ", capacity\t: " << b.capacity() << std::endl;
		for (int i = 1; i < 11; i++)
			a.push_back(i * 10);
		std::cout << "a vector\t, size\t:" << a.size() << ", capacity\t: " << a.capacity() << std::endl;
		for (const auto &element : a)
			std::cout << element << " -> ";
		std::cout << "end" << std::endl;
		std::cout << "b vector\t, size\t:" << b.size() << ", capacity\t: " << b.capacity() << std::endl;
		for (const auto &element : b)
			std::cout << element << " -> ";
		std::cout << "end" << std::endl << std::endl;
		a.resize(19);
		std::cout << "a.resize(19)\t, size\t:" << a.size() << ", capacity\t: " << a.capacity() << std::endl;
		for (const auto &element : a)
			std::cout << element << " -> ";
		std::cout << "end" << std::endl;
		b.resize(2, 3);
		std::cout << "b.resize(2, 3)\t, size\t:" << b.size() << ", capacity\t: " << b.capacity() << std::endl;
		for (const auto &element : b)
			std::cout << element << " -> ";
		std::cout << "end" << std::endl;
	}*/
	try
	{
		std::cout << "-------------중간-------------" << std::endl;
		std::vector<int>	a(10, 1);
		std::vector<int>::iterator	t = a.begin() + 3;
		std::cout << "size\t:" << a.size() << ", capacity\t: " << a.capacity() << std::endl;
		for (const auto &element : a)
			std::cout << element << " -> ";
		std::cout << "end" << std::endl;
		a.insert(t, 2);
		std::cout << "size\t:" << a.size() << ", capacity\t: " << a.capacity() << std::endl;
		for (const auto &element : a)
			std::cout << element << " -> ";
		std::cout << "end" << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	try
	{
		std::cout << "-------------음수-------------" << std::endl;
		std::vector<int>	a(10, 1);
		std::vector<int>::iterator	t = a.begin() - 3;
		std::cout << "size\t:" << a.size() << ", capacity\t: " << a.capacity() << std::endl;
		for (const auto &element : a)
			std::cout << element << " -> ";
		std::cout << "end" << std::endl;
		a.insert(t, 2);
		std::cout << "size\t:" << a.size() << ", capacity\t: " << a.capacity() << std::endl;
		for (const auto &element : a)
			std::cout << element << " -> ";
		std::cout << "end" << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	try
	{
		std::cout << "-------------넘어서-------------" << std::endl;
		std::vector<int>	a(10, 1);
		std::vector<int>::iterator	t = a.begin() + 13;
		std::cout << "size\t:" << a.size() << ", capacity\t: " << a.capacity() << std::endl;
		for (const auto &element : a)
			std::cout << element << " -> ";
		std::cout << "end" << std::endl;
		a.insert(t, 2);
		std::cout << "size\t:" << a.size() << ", capacity\t: " << a.capacity() << std::endl;
		for (const auto &element : a)
			std::cout << element << " -> ";
		std::cout << "end" << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	try
	{
		std::cout << "-------------더 넘어서-------------" << std::endl;
		std::vector<int>	a(10, 1);
		std::vector<int>::iterator	t = a.begin() + 23;
		std::cout << "size\t:" << a.size() << ", capacity\t: " << a.capacity() << std::endl;
		for (const auto &element : a)
			std::cout << element << " -> ";
		std::cout << "end" << std::endl;
		a.insert(t, 2);
		std::cout << "size\t:" << a.size() << ", capacity\t: " << a.capacity() << std::endl;
		for (const auto &element : a)
			std::cout << element << " -> ";
		std::cout << "end" << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);
}
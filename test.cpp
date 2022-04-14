#include <iterator>
#include <vector>
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
	std::vector<int>	a;
	std::vector<int>	b;
	std::vector<int>	c;
	std::vector<int>	d;
	int					temp(1);
	a.push_back(1);
	b.push_back(2);

	// a++;
	// ++a;
	// a--;
	// --a;
	// std::cout << "a : " << a << "\tb : " << b << std::endl;
	std::cout << "(a < b) : " << (a < b) << std::endl;
	std::cout << "(a > b) : " << (a > b) << std::endl;
	std::cout << "(a <= b) : " << (a <= b) << std::endl;
	std::cout << "(a >= b) : " << (a >= b) << std::endl;
	std::cout << "(a == b) : " << (a == b) << std::endl;
	std::cout << "(a != b) : " << (a != b) << std::endl;
	// a += temp;
	// std::cout << "(a += 1) : " << a << std::endl;
	// a -= temp;
	// std::cout << "(a -= 1) : " << a << std::endl;
	// c = a + temp;
	// d = a - temp;
	
	return (0);
}
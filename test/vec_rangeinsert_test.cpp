#include <iostream>
#include <vector>
#include <memory>

int	main(void)
{
	{
		try
		{
			std::cout << "-------------빔-------------" << std::endl;
			std::vector<int>	a;
			std::vector<int>::iterator	t = a.begin();
            std::cout << "begin\t: "<< &(*t) << std::endl;
			std::cout << "size\t:" << a.size() << ", capacity\t: " << a.capacity() << std::endl;
			for (const auto &element : a)
				std::cout << element << " -> ";
			std::cout << "end" << std::endl;
			std::cout << "a.insert(t, 2, 2) return value\t: " << &(*a.insert(t, 2, 2)) << std::endl;
			std::cout << "size\t:" << a.size() << ", capacity\t: " << a.capacity() << std::endl;
			for (const auto &element : a)
				std::cout << element << " -> ";
			std::cout << "end" << std::endl;
			for (int i = 0; i < a.size(); i++)
			std::cout << "a.at(" << i << ")\t: " << &a.at(i) << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}
	{
		try
		{
			std::cout << "-------------음수-------------" << std::endl;
			std::vector<int>	a(10, 1);
			std::vector<int>::iterator	t = a.begin() - 1;
            std::cout << "begin\t: "<< &(*a.begin()) << std::endl;
            std::cout << "begin - 1\t: "<< &(*t) << std::endl;
			std::cout << "size\t:" << a.size() << ", capacity\t: " << a.capacity() << std::endl;
			for (const auto &element : a)
				std::cout << element << " -> ";
			std::cout << "end" << std::endl;
			std::cout << "a.insert(t, 2, 2) return value\t: " << &(*a.insert(t, 2, 2)) << std::endl;
			std::cout << "size\t:" << a.size() << ", capacity\t: " << a.capacity() << std::endl;
			for (const auto &element : a)
				std::cout << element << " -> ";
			std::cout << "end" << std::endl;
			for (int i = 0; i < a.size(); i++)
			std::cout << "a.at(" << i << ")\t: " << &a.at(i) << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}
	{
		try
		{
			std::cout << "-------------중간-------------" << std::endl;
			std::vector<int>	a(10, 1);
			std::vector<int>::iterator	t = a.begin() + 5;
            std::cout << "begin\t: "<< &(*a.begin()) << std::endl;
            std::cout << "begin + 5\t: "<< &(*t) << std::endl;
			std::cout << "size\t:" << a.size() << ", capacity\t: " << a.capacity() << std::endl;
			for (const auto &element : a)
				std::cout << element << " -> ";
			std::cout << "end" << std::endl;
			std::cout << "a.insert(t, 2, 2) return value\t: " << &(*a.insert(t, 2, 2)) << std::endl;
			std::cout << "size\t:" << a.size() << ", capacity\t: " << a.capacity() << std::endl;
			for (const auto &element : a)
				std::cout << element << " -> ";
			std::cout << "end" << std::endl;
			for (int i = 0; i < a.size(); i++)
			std::cout << "a.at(" << i << ")\t: " << &a.at(i) << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}
	{
		try
		{
			std::cout << "-------------넘어서-------------" << std::endl;
			std::vector<int>	a(10, 1);
			std::vector<int>::iterator	t = a.begin() + 15;
            std::cout << "begin\t: "<< &(*a.begin()) << std::endl;
            std::cout << "begin + 15\t: "<< &(*t) << std::endl;
			std::cout << "size\t:" << a.size() << ", capacity\t: " << a.capacity() << std::endl;
			for (const auto &element : a)
				std::cout << element << " -> ";
			std::cout << "end" << std::endl;
			std::cout << "a.insert(t, 2, 2) return value\t: " << &(*a.insert(t, 2, 2)) << std::endl;
			std::cout << "size\t:" << a.size() << ", capacity\t: " << a.capacity() << std::endl;
			for (const auto &element : a)
				std::cout << element << " -> ";
			std::cout << "end" << std::endl;
			for (int i = 0; i < a.size(); i++)
			std::cout << "a.at(" << i << ")\t: " << &a.at(i) << std::endl;\
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}
	{
		try
		{
			std::cout << "-------------더 넘어서-------------" << std::endl;
			std::vector<int>	a(10, 1);
			std::vector<int>::iterator	t = a.begin() + 25;
            std::cout << "begin\t: "<< &(*a.begin()) << std::endl;
            std::cout << "begin + 25\t: "<< &(*t) << std::endl;
			std::cout << "size\t:" << a.size() << ", capacity\t: " << a.capacity() << std::endl;
			for (const auto &element : a)
				std::cout << element << " -> ";
			std::cout << "end" << std::endl;
			std::cout << "a.insert(t, 2, 2) return value\t: " << &(*a.insert(t, 2, 2)) << std::endl;
			std::cout << "size\t:" << a.size() << ", capacity\t: " << a.capacity() << std::endl;
			for (const auto &element : a)
				std::cout << element << " -> ";
			std::cout << "end" << std::endl;
			for (int i = 0; i < a.size(); i++)
			std::cout << "a.at(" << i << ")\t: " << &a.at(i) << std::endl;
			for (int i = 0; i < 16; i++)
			std::cout << "a.at(" << 10 + i << ")\t: " << &a.at(10 + i) << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}
	/*{
		try
		{
			std::cout << "-------------더더 넘어서-------------" << std::endl;
			std::vector<int>	a(10, 1);
			std::vector<int>::iterator	t = a.begin() + 4611686018427387904123;
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
	}*/
	return (0);
}
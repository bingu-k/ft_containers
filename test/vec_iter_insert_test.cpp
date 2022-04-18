#include <iostream>
#include <vector>
#include <memory>

int	main(void)
{
	std::vector<int>	b(10, 2);
    for (const auto &element : b)
		std::cout << element << " -> ";
    std::cout << "end" << std::endl;
	{
		try
		{
			std::cout << "-------------빔-------------" << std::endl;
			std::vector<int>	a;
			std::vector<int>::iterator	t = a.begin();
			std::cout << "size\t:" << a.size() << ", capacity\t: " << a.capacity() << std::endl;
			for (const auto &element : a)
				std::cout << element << " -> ";
			std::cout << "end" << std::endl;
			a.insert(t, b.begin(), b.end());
			std::cout << "a.insert(t, b.begin(), b.end())\t: " << std::endl;
			std::cout << "size\t:" << a.size() << ", capacity\t: " << a.capacity() << std::endl;
			for (const auto &element : a)
				std::cout << element << " -> ";
			std::cout << "end" << std::endl;
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
			std::vector<int>::iterator	t = a.begin() - 2;
			std::cout << "size\t:" << a.size() << ", capacity\t: " << a.capacity() << std::endl;
			for (const auto &element : a)
				std::cout << element << " -> ";
			std::cout << "end" << std::endl;
			a.insert(t, b.begin(), b.end());
			std::cout << "a.insert(t, b.begin(), b.end())\t: " << std::endl;
			std::cout << "size\t:" << a.size() << ", capacity\t: " << a.capacity() << std::endl;
			for (const auto &element : a)
				std::cout << element << " -> ";
			std::cout << "end" << std::endl;
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
			std::cout << "size\t:" << a.size() << ", capacity\t: " << a.capacity() << std::endl;
			for (const auto &element : a)
				std::cout << element << " -> ";
			std::cout << "end" << std::endl;
			a.insert(t, b.begin(), b.end());
			std::cout << "a.insert(t, b.begin(), b.end())\t: " << std::endl;
			std::cout << "size\t:" << a.size() << ", capacity\t: " << a.capacity() << std::endl;
			for (const auto &element : a)
				std::cout << element << " -> ";
			std::cout << "end" << std::endl;
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
			std::cout << "size\t:" << a.size() << ", capacity\t: " << a.capacity() << std::endl;
			for (const auto &element : a)
				std::cout << element << " -> ";
			std::cout << "end" << std::endl;
			a.insert(t, b.begin(), b.end());
			std::cout << "a.insert(t, b.begin(), b.end())\t: " << std::endl;
			std::cout << "size\t:" << a.size() << ", capacity\t: " << a.capacity() << std::endl;
			for (const auto &element : a)
				std::cout << element << " -> ";
			std::cout << "end" << std::endl;
			// for (int i = 0; i < 6; i++)
			//     std::cout << "a.at(" << 10 + i << ")\t: " << a.at(10 + i) << std::endl;
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
			std::cout << "size\t:" << a.size() << ", capacity\t: " << a.capacity() << std::endl;
			for (const auto &element : a)
				std::cout << element << " -> ";
			std::cout << "end" << std::endl;
			a.insert(t, b.begin(), b.end());
			std::cout << "a.insert(t, b.begin(), b.end())\t: " << std::endl;
			std::cout << "size\t:" << a.size() << ", capacity\t: " << a.capacity() << std::endl;
			for (const auto &element : a)
				std::cout << element << " -> ";
			std::cout << "end" << std::endl;
			// for (int i = 0; i < 16; i++)
			//     std::cout << "a.at(" << 10 + i << ")\t: " << a.at(10 + i) << std::endl;
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
#include <vector>
#include <iostream>

int	main(void)
{
	{
		try
		{
			std::cout << "-------------빔-------------" << std::endl;
			std::vector<int>	a;
			std::cout << "size\t:" << a.size() << ", capacity\t: " << a.capacity() << std::endl;
			for (const auto &element : a)
				std::cout << element << " -> ";
			std::cout << "end" << std::endl;
			a.reserve(1);
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
			std::vector<int>	a(5, 1);
			std::cout << "size\t:" << a.size() << ", capacity\t: " << a.capacity() << std::endl;
			for (const auto &element : a)
				std::cout << element << " -> ";
			std::cout << "end" << std::endl;
			a.reserve(-1);
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
			std::cout << "-------------내부-------------" << std::endl;
			std::vector<int>	a(5, 1);
			std::cout << "size\t:" << a.size() << ", capacity\t: " << a.capacity() << std::endl;
			for (const auto &element : a)
				std::cout << element << " -> ";
			std::cout << "end" << std::endl;
			a.reserve(2);
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
			std::cout << "-------------딱뎀-------------" << std::endl;
			std::vector<int>	a(5, 1);
			std::cout << "size\t:" << a.size() << ", capacity\t: " << a.capacity() << std::endl;
			for (const auto &element : a)
				std::cout << element << " -> ";
			std::cout << "end" << std::endl;
			a.reserve(5);
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
			std::cout << "-------------살짝 넘어감-------------" << std::endl;
			std::vector<int>	a(5, 1);
			std::cout << "size\t:" << a.size() << ", capacity\t: " << a.capacity() << std::endl;
			for (const auto &element : a)
				std::cout << element << " -> ";
			std::cout << "end" << std::endl;
			a.reserve(7);
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
			std::cout << "-------------냅다 넘어감-------------" << std::endl;
			std::vector<int>	a(5, 1);
			std::cout << "size\t:" << a.size() << ", capacity\t: " << a.capacity() << std::endl;
			for (const auto &element : a)
				std::cout << element << " -> ";
			std::cout << "end" << std::endl;
			a.reserve(15);
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
			std::cout << "-------------날아감-------------" << std::endl;
			std::vector<int>	a(5, 1);
			std::cout << "size\t:" << a.size() << ", capacity\t: " << a.capacity() << std::endl;
			for (const auto &element : a)
				std::cout << element << " -> ";
			std::cout << "end" << std::endl;
			a.reserve(101);
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
}
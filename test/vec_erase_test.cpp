#include <iostream>
#include <vector>
#include <memory>

int main(void)
{
	// {
	// 	try
	// 	{
	// 		std::vector<int>	a;
	// 		for (int i = 0; i < 10; i++)
	// 			a.push_back(i);
	// 		std::cout << "-------------더 음수-------------" << std::endl;
	// 		std::cout << "origin vector<int> a" << std::endl;
	// 		for (const auto& elem : a)
	// 			std::cout << elem << " -> ";
	// 		std::cout << "end" << std::endl;
	// 		std::cout << "erase position(-2) and return iterator value\t: " << *a.erase(a.begin() - 9) << std::endl;
	// 		for (const auto& elem : a)
	// 			std::cout << elem << " -> ";
	// 		std::cout << "end" << std::endl;
	// 	}
	// 	catch(const std::exception& e)
	// 	{
	// 		std::cerr << e.what() << '\n';
	// 	}
	// }
	// {
	// 	try
	// 	{
	// 		std::vector<int>	a;
	// 		for (int i = 0; i < 10; i++)
	// 			a.push_back(i);
	// 		std::cout << "-------------음수-------------" << std::endl;
	// 		std::cout << "origin vector<int> a" << std::endl;
	// 		for (const auto& elem : a)
	// 			std::cout << elem << " -> ";
	// 		std::cout << "end" << std::endl;
	// 		std::cout << "erase position(-1) and return iterator value\t: " << *a.erase(a.begin() - 1) << std::endl;
	// 		for (const auto& elem : a)
	// 			std::cout << elem << " -> ";
	// 		std::cout << "end" << std::endl;
	// 	}
	// 	catch(const std::exception& e)
	// 	{
	// 		std::cerr << e.what() << '\n';
	// 	}
	// }
	{
		try
		{
			std::vector<int>	a;
			for (int i = 0; i < 10; i++)
				a.push_back(i);
			std::cout << "-------------내부-------------" << std::endl;
			std::cout << "origin vector<int> a" << std::endl;
			for (const auto& elem : a)
				std::cout << elem << " -> ";
			std::cout << "end" << std::endl;
			std::cout << "erase position(3) and return iterator value\t: " << *a.erase(a.begin() + 3) << std::endl;
			for (const auto& elem : a)
				std::cout << elem << " -> ";
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
			std::vector<int>	a;
			for (int i = 0; i < 10; i++)
				a.push_back(i);
			std::cout << "-------------넘어감-------------" << std::endl;
			std::cout << "origin vector<int> a" << std::endl;
			for (const auto& elem : a)
				std::cout << elem << " -> ";
			std::cout << "end" << std::endl;
			std::cout << "erase position(9) and return iterator value\t: " << *a.erase(a.begin() + 9) << std::endl;
			for (const auto& elem : a)
				std::cout << elem << " -> ";
			std::cout << "end" << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}
	/*{
		try
		{
			std::vector<int>	a;
			for (int i = 0; i < 10; i++)
				a.push_back(i);
			std::cout << "-------------더 넘어감-------------" << std::endl;
			std::cout << "origin vector<int> a" << std::endl;
			for (const auto& elem : a)
				std::cout << elem << " -> ";
			std::cout << "end" << std::endl;
			std::cout << "erase position(115) and return iterator value\t: " << *a.erase(a.begin() + 115) << std::endl;
			for (const auto& elem : a)
				std::cout << elem << " -> ";
			std::cout << "end" << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}*/
	{
		try
		{
			std::vector<int>	a;
			for (int i = 0; i < 10; i++)
				a.push_back(i);
			std::cout << "-------------내부-------------" << std::endl;
			std::cout << "origin vector<int> a" << std::endl;
			for (const auto& elem : a)
				std::cout << elem << " -> ";
			std::cout << "end" << std::endl;
			std::cout << "erase position(3rd, 5th) and return iterator value\t: " << *a.erase(a.begin() + 3, a.begin() + 5) << std::endl;
			for (const auto& elem : a)
				std::cout << elem << " -> ";
			std::cout << "end" << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}
}
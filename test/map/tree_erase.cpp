#include <iostream>
#include <list>
#include "../../containers/map.hpp"
#include "../../containers/containers_test/srcs/base.hpp"

#define T1 int
#define T2 std::string
#define TESTED_NAMESPACE ft
#define _pair TESTED_NAMESPACE::pair
typedef _pair<const T1, T2> T3;

static int iter = 0;

template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
};

template <typename T_MAP>
void	printSize(T_MAP const &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	std::cout << "max_size: " << mp.max_size() << std::endl;
	if (print_content)
	{
		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it, false) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
};

template <typename MAP, typename U>
void	ft_erase(MAP &mp, U param)
{
	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	mp.erase(param);
	printSize(mp);
}

template <typename MAP, typename U, typename V>
void	ft_erase(MAP &mp, U param, V param2)
{
	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	mp.erase(param, param2);
	printSize(mp);
}

int		main(void)
{
	std::list<T3> lst;
	unsigned int lst_size = 10;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3(i, std::string((lst_size - i), i + 65)));
	TESTED_NAMESPACE::map<T1, T2> mp(lst.begin(), lst.end());
	printSize(mp);

	// mp.printMap();

	ft_erase(mp, ++mp.begin());	//1제거

	// mp.printMap();

	ft_erase(mp, mp.begin());	//0제거

	// mp.printMap();

	ft_erase(mp, --mp.end());	//9제거

	std::cout << "1, 0, 9 제거" << std::endl;
	// mp.printMap();

	ft_erase(mp, mp.begin(), ++(++(++mp.begin())));	//2~4제거

	std::cout << "2, 3, 4 제거" << std::endl;
	mp.printMap();
	
	ft_erase(mp, --(--(--mp.end())), --mp.end());	//6~7제거

	std::cout << "6, 7 제거" << std::endl;
	mp.printMap();
	mp[10] = "Hello";			//10추가
	mp[11] = "Hi there";		//11추가
	std::cout << "10, 11 추가" << std::endl;
	// mp.printMap();
	printSize(mp);
	ft_erase(mp, --(--(--mp.end())), mp.end());		//8~11제거

	std::cout << "8, 10, 11 제거" << std::endl;
	// mp.printMap();
	mp[12] = "ONE";				//12추가
	mp[13] = "TWO";				//13추가
	mp[14] = "THREE";			//14추가this->_end
	mp[15] = "FOUR";			//15추가

	std::cout << "12, 13, 14, 15 추가" << std::endl;
	// mp.printMap();
	printSize(mp);
	ft_erase(mp, mp.begin(), mp.end());				//전체제거
	std::cout << "전체 제거" << std::endl;
	// mp.printMap();
	system("leaks a.out");
	return (0);
}

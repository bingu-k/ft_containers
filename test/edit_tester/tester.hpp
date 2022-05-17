#ifndef TESTS_HPP
# define TESTS_HPP

# include <vector>
# include <map>
# include <stack>
# include <iostream>
# include "../../containers/vector.hpp"
# include "../../containers/map.hpp"
# include "../../containers/stack.hpp"

# ifdef __linux__
#  define RESET "\e[0m"
#  define GREEN "\e[92m"
#  define BLUE "\e[94m"
#  define BOLD "\e[1m"
# endif

# ifdef __APPLE__
#  define RESET "\e[0m"
#  define GREEN "\e[92m"
#  define BLUE "\e[94m"
#  define BOLD "\e[1m"
# endif

# define GOOD "✓"
# define FAIL "❌"

void	test_vector(void);
void	test_map(void);
void	test_stack(void);

inline void print_header(std::string str)
{
	int margin = (40 - str.length()) / 2;
	int width = (margin * 2 + str.length()) + 2;
	std::cout << BLUE << std::endl;
	std::cout << std::string(width, '*') << std::endl;
	std::cout << "*" << std::string(margin, ' ') << str << std::string(margin, ' ') << "*" << std::endl;
	std::cout << std::string(width, '*') << std::endl;
	std::cout << RESET;
};

template <typename T>
inline void check(std::string name, T a, T b)
{
	std::string margin(38 - name.length(), ' ');
	if (a == b)
		std::cout << name << ": " << margin << BOLD << GREEN << GOOD << RESET << std::endl;
	else
		std::cout << name << ": " << margin << FAIL << std::endl;
};

inline void check(std::string name, bool good)
{
	std::string margin(38 - name.length(), ' ');
	if (good)
		std::cout << name << ": " << margin << BOLD << GREEN << GOOD << RESET << std::endl;
	else
		std::cout << name << ": " << margin << FAIL << std::endl;
};

#endif
#include <iostream>
#include "../../containers/map.hpp"
#include <map>

int	main(void)
{
	std::map<int, int>	m;
	for (unsigned int i = 0; i < 10; ++i)
		m[i] = i;
	ft::map<int, int>	mp(m.begin(), m.end());
	return (0);
}
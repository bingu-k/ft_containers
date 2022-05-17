#include <iostream>
#include "../../containers/map.hpp"
#include <map>

int	main(void)
{
	std::map<int, int>	m;
	for (unsigned int i = 0; i < 10; ++i)
		m[i] = i;
	std::map<int, int>::iterator	it = m.begin();
	std::map<int, int>::const_iterator	ite = m.begin();
	
	// ft::map<int, int>	mp(m.begin(), m.end());
	return (0);
}
#include <vector>
#include <iostream>

int	main(void)
{
	double	s = 1;
	std::vector<int>	v(30, 1);
	std::vector<int>	res;

	for (int i = 0; i < 40; i++)
	{
		v.resize(s);
		res.push_back(v.size());
		res.push_back(v.capacity());
		s *= 2;
	}

	std::cerr << "\nstd\n";
	for (const auto& a : res)
		std::cerr << a << " -> ";
	std::cerr << "end" << std::endl;
}
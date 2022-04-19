#include "../vector.hpp"
#include <iostream>

using namespace std;

int	main(void)
{
	ft::vector<int>	a1;
	// ft::vector<int>	a2(10, 1);

	for (int i = 1; i < 6; i++)
		a1.push_back(i);
	cout << "a1.size()\t: " << a1.size() << "\ta1.capacity()\t: " << a1.capacity() << endl;
	for (const auto& ele : a1)
		cout << ele << " -> ";
	cout << "end" << endl;

	a1.resize(8);
	// a1.resize(13, 2);
	// a1.insert(a1.begin()+2, 4);
	// a1.erase(a1.end()-1);
	// a1.erase(a1.begin() + 5, a1.begin() + 5);

	cout << "a1.size()\t: " << a1.size() << "\ta1.capacity()\t: " << a1.capacity() << endl;
	for (const auto& ele : a1)
		cout << ele << " -> ";
	cout << "end" << endl;

	// cout << "==============Small Size===============" << endl;
	// cout << "a2.size()\t: " << a2.size() << "\ta2.capacity()\t: " << a2.capacity() << endl;
	// for (const auto& ele : a2)
	// 	cout << ele << " -> ";
	// cout << "end" << endl;

	// a2.resize(7);

	// cout << "a2.size()\t: " << a2.size() << "\ta2.capacity()\t: " << a2.capacity() << endl;
	// for (const auto& ele : a2)
	// 	cout << ele << " -> ";
	// cout << "end" << endl;
	return (0);
}
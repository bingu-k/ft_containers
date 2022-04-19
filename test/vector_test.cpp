#include <vector>
#include <iostream>
#include <cstddef>

using namespace std;

int	main(void)
{
	vector<int>	a1;
	vector<int>	a2(10, 1);

	for (int i = 1; i < 6; i++)
		a1.push_back(i);
	cout << "a1.size()\t: " << a1.size() << "\ta1.capacity()\t: " << a1.capacity() << endl;
	for (const auto& ele : a1)
		cout << ele << " -> ";
	cout << "end" << endl;

	// a1.resize(30);
	// a1.insert(a1.begin()+2, 4, 2);
	// a1.erase(a1.end());
	a1.erase(a1.begin() + 1, a1.begin() + 3);

	cout << "a1.size()\t: " << a1.size() << "\ta1.capacity()\t: " << a1.capacity() << endl;
	vector<int>::iterator it = a1.begin();
	for (; it != a1.end(); it++)
		cout << *it << " -> ";
	cout << "end" << endl;

	/*
	cout << "a2.size()\t: " << a2.size() << "\ta2.capacity()\t: " << a2.capacity() << endl;
	for (const auto& ele : a2)
		cout << ele << " -> ";
	cout << "end" << endl;

	a2.resize(7);

	cout << "a2.size()\t: " << a2.size() << "\ta2.capacity()\t: " << a2.capacity() << endl;
	for (const auto& ele : a2)
		cout << ele << " -> ";
	cout << "end" << endl;*/
	return (0);
}
#include <iostream>
#include <map>

using namespace std;

int main(void)
{
	map<char, int>  a;
	map<char, int>  b;

	a.insert(pair<char, int>('a', 100));
	a.insert(pair<char, int>('d', 400));
	a.insert(pair<char, int>('e', 500));
	a.insert(pair<char, int>('b', 200));
	a.insert(pair<char, int>('c', 300));

	b.insert(pair<char, int>('a', 100));
	b.insert(pair<char, int>('d', 400));
	b.insert(pair<char, int>('e', 500));
	b.insert(pair<char, int>('b', 200));
	b.insert(pair<char, int>('c', 300));
	// for (pair<char, int> q : b)
	// 	std::cout << q.first << ":" << q.second << std::endl;
	// b.insert(a.begin(), a.find('c'));
	std::cout << "\tmap b" << std::endl;
	for (pair<char, int> q : b)
		std::cout << q.first << ":" << q.second << std::endl;

	// a.erase(b.find('b'), b.find('d'));
	std::cout << a.erase('c') << a.erase('b');
	std::cout << "\tmap a" << std::endl;
	for (pair<char, int> q : a)
		std::cout << q.first << ":" << q.second << std::endl;
	return (0);
};
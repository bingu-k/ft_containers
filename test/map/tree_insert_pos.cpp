#include <iostream>
#include <map>

using namespace std;

int main(void)
{
	map<char, int>  a;

	a.insert(pair<char, int>('a', 100));
	a.insert(pair<char, int>('d', 400));
	a.insert(pair<char, int>('e', 500));
	a.insert(pair<char, int>('c', 300));

	std::cout << "\tmap original a" << std::endl;
	for (pair<char, int> q : a)
		std::cout << q.first << ":" << q.second << std::endl;
	pair<char, int> double_check('a', 100);
	pair<char, int> pos_check('b', 200);
	pair<char, int> next_pos_check('f', 600);
	pair<char, int> double_next_check('g', 700);

	map<char, int>::iterator	start = a.begin();
	map<char, int>::iterator	last = a.find('e');
	a.insert(start, double_check);
	a.insert(last, pos_check);
	a.insert(last, next_pos_check);
	a.insert(start, double_next_check);
	std::cout << "\tmap change a" << std::endl;
	for (pair<char, int> q : a)
		std::cout << q.first << ":" << q.second << std::endl;
	return (0);
};
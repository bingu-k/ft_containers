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

	std::cout << "\tmap original a" << std::endl;
	for (pair<char, int> q : a)
		std::cout << q.first << ":" << q.second << std::endl;
    
    map<char, int>::iterator    low = a.lower_bound('d');
    map<char, int>::iterator    upp = a.upper_bound('d');

    std::cout << (*low).first << "\t: " << (*low).second << std::endl;
    std::cout << (*upp).first << "\t: " << (*upp).second << std::endl;
	return (0);
};
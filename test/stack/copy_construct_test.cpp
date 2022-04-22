#include "../../containers/stack.hpp"
#include <list>
#include <iostream>

#define TESTED_TYPE int
typedef std::list<TESTED_TYPE> container_type;
#define t_stack_ ft::stack<TESTED_TYPE, container_type>

void printSize(t_stack_ st)
{
	while (st.size())
	{
		std::cout << st.top() << " -> ";
		st.pop(); 
	}
	std::cout << "end" << std::endl;
}

int		main(void)
{
	container_type	ctnr;

	ctnr.push_back(21);
	ctnr.push_back(42);
	ctnr.push_back(1337);
	ctnr.push_back(19);
	ctnr.push_back(0);
	ctnr.push_back(183792);

	t_stack_		stck(ctnr);

	std::cout << "empty: " << stck.empty() << std::endl;
	std::cout << "size: " << stck.size() << std::endl;

	stck.push(1);
	stck.push(2);
	stck.push(3);
	stck.push(4);
	stck.push(5);
	stck.push(6);

	std::cout << "Added some elements" << std::endl;

	std::cout << "empty: " << stck.empty() << std::endl;
	printSize(stck);

	return (0);
}

#include "tester.hpp"
#include <time.h>

#define TEST_NAME	std

static void constructors(void)
{
	print_header("Constructor");
	TEST_NAME::stack<int> q1;
	TEST_NAME::stack<int> q2;
	check("q1.size() == q2.size()", q1.size() == q2.size());
	check("q1.empty() == q2.empty()", q1.empty() == q2.empty());
}

static void front_back(void)
{
	print_header("Front / Back / Push / Pop");
	TEST_NAME::stack<int> q1;
	TEST_NAME::stack<int> q2;
	q1.push(0);
	q1.push(1);
	q1.push(2);
	q2.push(0);
	q2.push(1);
	q2.push(2);
	check("q1.size() == q2.size()", q1.size() == q2.size());
	check("q1.empty() == q2.empty()", q1.empty() == q2.empty());
	check("q1.top() == q2.top()", q1.top(), q2.top());
	q1.pop();
	q2.pop();
	check("q1.size() == q2.size()", q1.size() == q2.size());
	check("q1.top() == q2.top()", q1.top(), q2.top());
}

int	main(void)
{
	clock_t	start = clock();
	print_header("stack");
	constructors();
	front_back();
	clock_t end = clock();
	double	result = static_cast<double>(end - start);
	std::cout << "Total time\t: " << result << " ms" << std::endl;
	return(0);
}
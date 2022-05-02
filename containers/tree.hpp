#ifndef TREE_HPP
# define TREE_HPP

template <class T, class Compare, class Alloc>
class tree
{
public:
	typedef T						value_type;
	typedef Compare					value_compare;
	typedef Alloc					allocator_type;
private:
	/* data */
public:
	tree(/* args */);
	~tree();
};

#endif
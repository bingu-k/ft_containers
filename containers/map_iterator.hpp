#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include "utils.hpp"
# include "iterator.hpp"

namespace ft
{
	// map_iterator
	template <class iterator, class P>
	class map_iterator
	{
	public:
		typedef iterator									tree_iter;
		typedef P											value_type;
		typedef ft::bidirectional_iterator_tag				iterator_category;
		typedef ft::iterator<iterator_category(), value_type>
															iter;
		typedef typename iter::pointer						pointer;
		typedef typename iter::reference					reference;
		typedef typename iter::difference_type				difference_type;
	private:
		tree_iter	_elem;
		tree_iter	get_tree_iter(void) const { return (this->_elem); };
	public:
		map_iterator(tree_iter elem = m_nullptr)
		: _elem(elem) {};
		map_iterator(const map_iterator& x)
		: _elem(x._elem) {};
		map_iterator&	operator=(const map_iterator& x)
		{
			if (this != &x)
				this->_elem = x._elem;
			return (*this);
		};
		~map_iterator() {};

		reference	operator*() const
		{ return (this->_elem->get_node()); };
		pointer		operator->() const
		{ return (&(this->_elem->get_node())); };
		map_iterator&	operator++()
		{
			++(this->_elem);
			return (*this)
		};
		map_iterator&	operator++(int)
		{
			map_iterator	res(*this);
			++(*this);
			return (res);
		};
		map_iterator&	operator--()
		{
			--(this->_elem);
			return (*this)
		};
		map_iterator&	operator--(int)
		{
			map_iterator	res(*this);
			--(*this);
			return (res);
		};
		bool	operator==(const map_iterator& x, const map_iterator& y)
		{ return (x._elem == y._elem); };
		bool	operator!=(const map_iterator& x, const map_iterator& y)
		{ return (x._elem != y._elem); };
	};

	template <class iterator, class P>
	class map_const_iterator
	{
	public:
		typedef iterator									tree_iter;
		typedef P											value_type;
		typedef ft::bidirectional_iterator_tag				iterator_category;
		typedef ft::iterator<iterator_category(), value_type>
															iter;
		typedef typename iter::pointer						pointer;
		typedef typename iter::reference					reference;
		typedef typename iter::difference_type				difference_type;
	private:
		tree_iter	_elem;
		tree_iter	get_tree_iter(void) const { return (this->_elem); };
	public:
		map_const_iterator(tree_iter elem = m_nullptr)
		: _elem(elem) {};
		map_const_iterator(const map_const_iterator& x)
		: _elem(x._elem) {};
		map_const_iterator(const map_iterator<tree_iter, value_type>& x)
		: _elem(x.get_tree_iter()) {};
		map_const_iterator&	operator=(const map_const_iterator& x)
		{
			if (this != &x)
				this->_elem = x._elem;
			return (*this);
		};
		~map_const_iterator() {};

		reference	operator*() const
		{ return (this->_elem->get_node()); };
		pointer		operator->() const
		{ return (&(this->_elem->get_node())); };
		map_const_iterator&	operator++()
		{
			++(this->_elem);
			return (*this)
		};
		map_const_iterator&	operator++(int)
		{
			map_const_iterator	res(*this);
			++(*this);
			return (res);
		};
		map_const_iterator&	operator--()
		{
			--(this->_elem);
			return (*this)
		};
		map_const_iterator&	operator--(int)
		{
			map_const_iterator	res(*this);
			--(*this);
			return (res);
		};
		bool	operator==(const map_const_iterator& x, const map_const_iterator& y)
		{ return (x._elem == y._elem); };
		bool	operator!=(const map_const_iterator& x, const map_const_iterator& y)
		{ return (x._elem != y._elem); };
	};

	// tree_iterator
	template <class InputIter>
	inline InputIter&	tree_next_iter(InputIter me)
	{
		if (me->_right != m_nullptr)		// end()가 아니면 오른쪽 자식 하위 노드중 가장 작은것.
		{
			me = me->_right;
			while (me->_left != m_nullptr)
				me = me->_left;
			return (me);
		}
		while (me->_parent->_right == me) // 본인이 오른쪽 자식이면 하위노드중 가장 큰 값.
			me = me->_parent;
		return (me->_parent);
	};

	template <class InputIter>
	inline InputIter&	tree_prev_iter(InputIter me)
	{
		if (me->_left != m_nullptr)		// end()가 아니면 왼쪽 자식 하위 노드중 가장 큰것.
		{
			me = me->_left;
			while (me->_right != m_nullptr)
				me = me->_right;
			return (me);
		}
		while ((me->_parent->_left == me)) // 본인이 왼쪽자식이면 하위노드중 가장 작은 값.
			me = me->_parent;
		return (me->_parent);
	};

	template <class N, class P>
	class tree_iterator
	{
	public:
		typedef N												nodeptr;
		typedef P												value_type;
		typedef ft::bidirectional_iterator_tag					iterator_category;
		typedef ft::iterator<iterator_category(), value_type>	iter;
		typedef typename iter::pointer							pointer;
		typedef typename iter::reference						reference;
		typedef typename iter::difference_type					difference_type;
	private:
		nodeptr	_elem;
		nodeptr	get_nodeptr(void) const { return (this->_elem); };
	public:
		tree_iterator(nodeptr elem = m_nullptr)
		: _elem(elem) {};
		tree_iterator(const tree_iterator& x)
		: _elem(x.get_nodeptr()) {};
		tree_iterator&	operator=(const tree_iterator& x)
		{
			if (this != &x)
				this->_elem = x.get_nodeptr();
			return (*this);
		};
		~tree_iterator() {};

		reference	operator*() const
		{ return (this->get_nodeptr()->_value); };
		pointer		operator->() const
		{ return (&(this->get_nodeptr()->_value)); };
		tree_iterator&	operator++()
		{
			tree_next_iter(*this);
			return (*this);
		};
		tree_iterator&	operator++(int)
		{
			nodeptr	res(this->get_nodeptr());
			tree_next_iter(*this);
			return (res);
		};
		tree_iterator&	operator--()
		{
			tree_prev_iter(*this);
			return (*this);
		};
		tree_iterator&	operator--(int)
		{
			nodeptr	res(this->get_nodeptr());
			tree_prev_iter(*this);
			return (res);
		};
		bool	operator==(const tree_iterator& x, const tree_iterator& y)
		{ return (&(x.get_nodeptr()) == &(y.get_nodeptr())); };
		bool	operator!=(const tree_iterator& x, const tree_iterator& y)
		{ return !(x == y); };
	};
	template <class N, class P>
	class tree_const_iterator
	{
	public:
		typedef N												nodeptr;
		typedef P												value_type;
		typedef ft::bidirectional_iterator_tag					iterator_category;
		typedef ft::iterator<iterator_category(), value_type>	iter;
		typedef typename iter::pointer							pointer;
		typedef typename iter::reference						reference;
		typedef typename iter::difference_type					difference_type;
	private:
		nodeptr	_elem;
		nodeptr	get_nodeptr(void) const { return (this->_elem); };
	public:
		tree_const_iterator(nodeptr elem = m_nullptr)
		: _elem(elem) {};
		tree_const_iterator(const tree_const_iterator& x)
		: _elem(x.get_nodeptr()) {};
		tree_const_iterator(const tree_iterator<nodeptr, value_type>& x)
		: _elem(x.get_nodeptr()) {};
		tree_const_iterator&	operator=(const tree_const_iterator& x)
		{
			if (this != &x)
				this->_elem = x.get_nodeptr();
			return (*this);
		};
		~tree_const_iterator() {};

		reference	operator*() const
		{ return (this->get_nodeptr()->_value); };
		pointer		operator->() const
		{ return (&(this->get_nodeptr()->_value)); };
		tree_const_iterator&	operator++()
		{
			this->_elem = tree_next_iter(this->get_nodeptr());
			return (*this);
		};
		tree_const_iterator&	operator++(int)
		{
			nodeptr	res(this->get_nodeptr());
			this->_elem = tree_next_iter(this->get_nodeptr());
			return (res);
		};
		tree_const_iterator&	operator--()
		{
			this->_elem = tree_prev_iter(this->get_nodeptr());
			return (*this);
		};
		tree_const_iterator&	operator--(int)
		{
			this->_elem = tree_prev_iter(this->get_nodeptr());
			tree_prev_iter(*this);
			return (res);
		};
		bool	operator==(const tree_const_iterator& x, const tree_const_iterator& y)
		{ return (&(x.get_nodeptr()) == &(y.get_nodeptr())); };
		bool	operator!=(const tree_const_iterator& x, const tree_const_iterator& y)
		{ return !(x == y); };
	};
}

#endif
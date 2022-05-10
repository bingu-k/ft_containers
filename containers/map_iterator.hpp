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
		{ return (*(this->_elem)); };
		pointer		operator->() const
		{ return (&(*(this->_elem))); };
		map_iterator&	operator++()
		{
			++(this->_elem);
			return (*this);
		};
		map_iterator	operator++(int)
		{
			map_iterator	res(*this);
			++(*this);
			return (res);
		};
		map_iterator&	operator--()
		{
			--(this->_elem);
			return (*this);
		};
		map_iterator	operator--(int)
		{
			map_iterator	res(*this);
			--(*this);
			return (res);
		};
		friend bool	operator==(const map_iterator& x, const map_iterator& y)
		{ return (x._elem == y._elem); };
		friend bool	operator!=(const map_iterator& x, const map_iterator& y)
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

		tree_iter	get_tree_iter(void) const { return (this->_elem); };
		reference	operator*() const
		{ return (*(this->_elem)); };
		pointer		operator->() const
		{ return (&(*(this->_elem))); };
		map_const_iterator&	operator++()
		{
			++(this->_elem);
			return (*this);
		};
		map_const_iterator	operator++(int)
		{
			map_const_iterator	res(*this);
			++(*this);
			return (res);
		};
		map_const_iterator&	operator--()
		{
			--(this->_elem);
			return (*this);
		};
		map_const_iterator	operator--(int)
		{
			map_const_iterator	res(*this);
			--(*this);
			return (res);
		};
		friend bool	operator==(const map_const_iterator& x, const map_const_iterator& y)
		{ return (x._elem == y._elem); };
		friend bool	operator!=(const map_const_iterator& x, const map_const_iterator& y)
		{ return (x._elem != y._elem); };
	};

	// tree_iterator
	template <class nodeptr>
	inline nodeptr	tree_next_iter(nodeptr& me)
	{
		if (me->_right != m_nullptr)
		{	// end()가 아니면 오른쪽 자식 하위 노드중 가장 작은것.
			me = me->_right;
			while (me->_left != m_nullptr)
				me = me->_left;
			return (me);
		}
		while (me->_parent->_right == me) // 본인이 오른쪽 자식이면 하위노드중 가장 큰 값.
			me = me->_parent;
		return (me->_parent);
	};

	template <class nodeptr>
	inline nodeptr	tree_prev_iter(nodeptr& me)
	{
		if (me->_left != m_nullptr)
		{	// end()가 아니면 왼쪽 자식 하위 노드중 가장 큰것.
			me = me->_left;
			while (me->_right != m_nullptr)
				me = me->_right;
			return (me);
		}
		while (me->_parent->_left == me) // 본인이 왼쪽자식이면 하위노드중 가장 작은 값.
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
		nodeptr	_root;
		nodeptr	_nil;
	public:
		tree_iterator(nodeptr elem = m_nullptr, nodeptr root = m_nullptr, nodeptr nil = m_nullptr)
		: _elem(elem), _root(root), _nil(nil) {};
		tree_iterator(const tree_iterator& x)
		: _elem(x.get_nodeptr()), _root(x.get_root()), _nil(x.get_nil()) {};
		tree_iterator&	operator=(const tree_iterator& x)
		{
			if (this != &x)
			{
				this->_elem = x.get_nodeptr();
				this->_root = x.get_root();
				this->_nil = x.get_nil();
			}
			return (*this);
		};
		~tree_iterator() {};

		nodeptr	get_nodeptr(void) const { return (this->_elem); };
		nodeptr	get_root(void) const { return (this->_root); };
		nodeptr	get_nil(void) const { return (this->_nil); };
		reference	operator*() const
		{ return (this->get_nodeptr()->_val); };
		pointer		operator->() const
		{ return (&(this->get_nodeptr()->_val)); };
		tree_iterator&	operator++()
		{
			if (this->_elem->_right != this->_nil)
			{
				this->_elem = this->_elem->_right;
				while (this->_elem->_left != this->_nil)
					this->_elem = this->_elem->_left;
			}
			while (this->_elem->_parent->_right == this->_elem)
				this->_elem = this->_elem->_parent;
			this->_elem = this->_elem->_parent;
			return (*this);
		};
		tree_iterator	operator++(int)
		{
			tree_iterator	res(*this);
			++(*this);
			return (res);
		};
		tree_iterator&	operator--()
		{
			if (this->_elem == this->_nil)
			{
				this->_elem = this->get_root();
				while (this->_elem->_right == this->_nil)
					this->_elem = this->_elem->_right;
			}
			else
			{
				if (this->_elem->_left != this->_nil)
				{	// end()가 아니면 왼쪽 자식 하위 노드중 가장 큰것.
					this->_elem = this->_elem->_left;
					while (this->_elem->_right != this->_nil)
						this->_elem = this->_elem->_right;
				}
				while (this->_elem->_parent->_left == this->_elem) // 본인이 왼쪽자식이면 하위노드중 가장 작은 값.
					this->_elem = this->_elem->_parent;
				this->_elem = this->_elem->_parent;
			}
			return (*this);
		};
		tree_iterator	operator--(int)
		{
			tree_iterator	res(*this);
			--(*this);
			return (res);
		};
		friend bool	operator==(const tree_iterator& x, const tree_iterator& y)
		{ return (x.get_nodeptr() == y.get_nodeptr()); };
		friend bool	operator!=(const tree_iterator& x, const tree_iterator& y)
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
		nodeptr	_root;
		nodeptr	_nil;
	public:
		tree_const_iterator(nodeptr elem = m_nullptr, nodeptr root = m_nullptr, nodeptr nil = m_nullptr)
		: _elem(elem), _root(root), _nil(nil) {};
		tree_const_iterator(const tree_const_iterator& x)
		: _elem(x.get_nodeptr()), _root(x.get_root()), _nil(x.get_nil()) {};
		tree_const_iterator(const tree_iterator<nodeptr, value_type>& x)
		: _elem(x.get_nodeptr()), _root(x.get_root()), _nil(x.get_nil()) {};
		tree_const_iterator&	operator=(const tree_const_iterator& x)
		{
			if (this != &x)
			{
				this->_elem = x.get_nodeptr();
				this->_root = x.get_root();
				this->_nil = x.get_nil();
			}
			return (*this);
		};
		~tree_const_iterator() {};

		nodeptr	get_nodeptr(void) const { return (this->_elem); };
		nodeptr	get_root(void) const { return (this->_root); };
		nodeptr	get_nil(void) const { return (this->_nil); };
		reference	operator*() const
		{ return (this->get_nodeptr()->_val); };
		pointer		operator->() const
		{ return (&(this->get_nodeptr()->_val)); };
		tree_const_iterator&	operator++()
		{
			this->_elem = tree_next_iter(this->_elem);
			return (*this);
		};
		tree_const_iterator	operator++(int)
		{
			tree_const_iterator	res(*this);
			++(*this);
			return (res);
		};
		tree_const_iterator&	operator--()
		{
			if (this->_elem == this->_nil)
			{
				this->_elem = this->get_root();
				while (this->_elem->_right == this->_nil)
					this->_elem = this->_elem->_right;
			}
			else
				this->_elem = tree_prev_iter(this->_elem);
			return (*this);
		};
		tree_const_iterator	operator--(int)
		{
			tree_const_iterator	res(*this);
			--(*this);
			return (res);
		};
		friend bool	operator==(const tree_const_iterator& x, const tree_const_iterator& y)
		{ return (x.get_nodeptr() == y.get_nodeptr()); };
		friend bool	operator!=(const tree_const_iterator& x, const tree_const_iterator& y)
		{ return !(x == y); };
	};
}

#endif
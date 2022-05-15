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
		map_iterator(tree_iter elem = tree_iter())
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

		tree_iter	get_tree_iter(void) const { return (this->_elem); };
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
		typedef ft::iterator<iterator_category(), const value_type>
															iter;
		typedef typename iter::pointer						pointer;
		typedef typename iter::reference					reference;
		typedef typename iter::difference_type				difference_type;
	private:
		tree_iter	_elem;
	public:
		map_const_iterator(tree_iter elem = tree_iter())
		: _elem(elem) {};
		map_const_iterator(const map_const_iterator& x)
		: _elem(x._elem) {};
		map_const_iterator(const map_iterator<typename tree_iter::non_const_tree_iter
											, value_type>& x)
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
		template <class, class> friend class tree_const_iterator;
	};

	// tree_iterator
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
		nodeptr	_end;
	public:
		tree_iterator(nodeptr elem = m_nullptr, nodeptr end = m_nullptr)
		: _elem(elem), _end(end) {};
		tree_iterator(const tree_iterator& x)
		: _elem(x.get_nodeptr()), _end(x.get_end()) {};
		tree_iterator&	operator=(const tree_iterator& x)
		{
			if (this != &x)
			{
				this->_elem = x.get_nodeptr();
				this->_end = x.get_end();
			}
			return (*this);
		};
		~tree_iterator() {};

		nodeptr	get_nodeptr(void) const { return (this->_elem); };
		nodeptr	get_end(void) const { return (this->_end); };
		reference	operator*() const
		{ return (this->get_nodeptr()->_val); };
		pointer		operator->() const
		{ return (&(this->get_nodeptr()->_val)); };
		tree_iterator&	operator++()
		{
			if (this->_elem->_right == this->_end)
				this->_elem = this->_elem->_right;
			else if (!is_nil(this->_elem->_right))
			{
				this->_elem = this->_elem->_right;
				while (!is_nil(this->_elem->_left))
					this->_elem = this->_elem->_left;
			}
			else
			{
				while (this->_elem->_parent->_left != this->_elem)
					this->_elem = this->_elem->_parent;
				this->_elem = this->_elem->_parent;
			}
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
			if (this->_elem == this->get_end())
				this->_elem = this->_elem->_parent;
			else if (!is_nil(this->_elem->_left))
			{	// end()가 아니면 왼쪽 자식 하위 노드중 가장 큰것.
				this->_elem = this->_elem->_left;
				while (!is_nil(this->_elem->_right))
					this->_elem = this->_elem->_right;
			}
			else
			{
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
		typedef tree_iterator<nodeptr, value_type>				non_const_tree_iter;
		nodeptr	_elem;
		nodeptr	_end;
	public:
		tree_const_iterator(nodeptr elem = m_nullptr, nodeptr end = m_nullptr)
		: _elem(elem), _end(end) {};
		tree_const_iterator(const tree_const_iterator& x)
		: _elem(x.get_nodeptr()), _end(x.get_end()) {};
		tree_const_iterator(const tree_iterator<nodeptr, value_type>& x)
		: _elem(x.get_nodeptr()), _end(x.get_end()) {};
		tree_const_iterator&	operator=(const tree_const_iterator& x)
		{
			if (this != &x)
			{
				this->_elem = x.get_nodeptr();
				this->_end = x.get_end();
			}
			return (*this);
		};
		~tree_const_iterator() {};

		nodeptr	get_nodeptr(void) const { return (this->_elem); };
		nodeptr	get_end(void) const { return (this->_end); };
		reference	operator*() const
		{ return (this->get_nodeptr()->_val); };
		pointer		operator->() const
		{ return (&(this->get_nodeptr()->_val)); };
		tree_const_iterator&	operator++()
		{
			if (this->_elem->_right == this->_end)
				this->_elem = this->_elem->_right;
			else if (!is_nil(this->_elem->_right))
			{
				this->_elem = this->_elem->_right;
				while (!is_nil(this->_elem->_left))
					this->_elem = this->_elem->_left;
			}
			else
			{
				while (this->_elem->_parent->_left != this->_elem)
					this->_elem = this->_elem->_parent;
				this->_elem = this->_elem->_parent;
			}
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
			if (this->_elem == this->get_end())
				this->_elem = this->_elem->_parent;
			else if (!is_nil(this->_elem->_left))
			{	// end()가 아니면 왼쪽 자식 하위 노드중 가장 큰것.
				this->_elem = this->_elem->_left;
				while (!is_nil(this->_elem->_right))
					this->_elem = this->_elem->_right;
			}
			else
			{
				while (this->_elem->_parent->_left == this->_elem) // 본인이 왼쪽자식이면 하위노드중 가장 작은 값.
					this->_elem = this->_elem->_parent;
				this->_elem = this->_elem->_parent;
			}
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
		template <class, class> friend class map_const_iterator;
	};
}

#endif
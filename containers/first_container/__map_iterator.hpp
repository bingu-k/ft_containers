#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

#include "iterator.hpp"
#include "tree.hpp"

namespace ft
{
	template <class TreeIter>
	class map_iterator
	{
		public:
			typedef TreeIter							iterator_type;
			typedef typename TreeIter::value_type		value_type;
			typedef ft::bidirectional_iterator_tag		iterator_category;
			typedef typename TreeIter::pointer			pointer;
			typedef typename TreeIter::reference		reference;
			typedef typename TreeIter::difference_type	difference_type;
			typedef typename TreeIter::size_type		size_type;
		private:
			iterator_type	_iter;
		public:
			map_iterator() : _iter(iterator_type()) {};
			map_iterator(const map_iterator& origin)
			: _iter(origin._iter) {};
			map_iterator&	operator=(const map_iterator& origin)
			{
				if (this != &origin)
					this->_iter = origin._iter;
				return (*this);
			};
			iterator_type	get_iter(void) const { return (_iter); };
		    reference	operator*(void) const { return (*_iter); };
			pointer		operator->(void) const { return (&(*_iter));};
			map_iterator&	operator++()
			{
				++_iter;
				return (*this);
			};
			map_iterator	operator++(int)
			{
				map_iterator	temp(*this);
				++(*this);
				return (temp);
			};
			map_iterator&	operator--()
			{
				--_iter;
				return (*this);
			};
			map_iterator	operator--(int)
			{
				map_iterator	temp(*this);
				--(*this);
				return (temp);
			};
    		friend bool	operator==(const map_iterator& x, const map_iterator& y)
			{ return (x._iter == y._iter); };
			friend bool	operator!=(const map_iterator& x, const map_iterator& y)
			{ return (x._iter != y._iter); };
	};

	template <class TreeIter>
	class map_const_iterator
	{
		template <class> friend	class tree_const_iterator;
		public:
			typedef TreeIter							iterator_type;
			typedef typename TreeIter::value_type		value_type;
			typedef ft::bidirectional_iterator_tag		iterator_category;
			typedef typename TreeIter::pointer			pointer;
			typedef typename TreeIter::reference		reference;
			typedef typename TreeIter::difference_type	difference_type;
			typedef typename TreeIter::size_type		size_type;
		private:
			iterator_type	_iter;
		public:
			map_const_iterator() : _iter(iterator_type()) {};
			map_const_iterator(const map_iterator<typename TreeIter::non_const_iter>& origin)
			: _iter(origin._iter) {};
			map_const_iterator(const map_const_iterator& origin)
			: _iter(origin._iter) {};
			map_const_iterator&	operator=(const map_const_iterator& origin)
			{
				if (this != &origin)
					this->_iter = origin._iter;
				return (*this);
			};
			iterator_type	get_iter(void) const { return (_iter); };
		    reference	operator*(void) const { return (*_iter); };
			pointer		operator->(void) const { return (&(*_iter));};
			map_const_iterator&	operator++()
			{
				++_iter;
				return (*this);
			};
			map_const_iterator	operator++(int)
			{
				map_const_iterator	temp(*this);
				++(*this);
				return (temp);
			};
			map_const_iterator&	operator--()
			{
				--_iter;
				return (*this);
			};
			map_const_iterator	operator--(int)
			{
				map_const_iterator	temp(*this);
				--(*this);
				return (temp);
			};
    		friend bool	operator==(const map_const_iterator& x, const map_const_iterator& y)
			{ return (x._iter == y._iter); };
			friend bool	operator!=(const map_const_iterator& x, const map_const_iterator& y)
			{ return (x._iter != y._iter); };
	};
};

#endif
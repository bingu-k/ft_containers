#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

# include "iterator.hpp"
# include "utils.hpp"

namespace ft
{
	template <typename T>
	class vector_iterator
	{
	public:
		// Typedef Member types
		typedef T												iterator_type;
		typedef ft::iterator<random_access_iterator_tag(), T>	iter;
		typedef typename iter::value_type						value_type;
		typedef typename iter::difference_type					difference_type;
		typedef typename iter::pointer							pointer;
		typedef typename iter::reference						reference;
		typedef typename iter::iterator_category				iterator_category;
	private:
		// Element
		pointer	_elem;
	public:
		// constractor
		vector_iterator(void)
		: _elem(0) {};
		vector_iterator(pointer elem)
		: _elem(elem) {};
		vector_iterator(const vector_iterator &origin)
		: _elem(origin.base()) {};
		~vector_iterator(void)
		{};

		pointer		base(void) const { return(_elem); };

		// Operator overloading
		vector_iterator	&operator=(const vector_iterator &origin)
		{
			if (this != &origin)
				_elem = origin._elem;
			return (*this);
		};
		vector_iterator	&operator+=(difference_type n)
		{
			this->_elem += n;
			return (*this);
		};
		vector_iterator	&operator-=(difference_type n)
		{
			this->_elem -= n;
			return (*this);
		};
		vector_iterator	&operator++(void)
		{
			++_elem;
			return (*this);
		};
		vector_iterator	operator++(int)
		{
			vector_iterator	temp(*this);
			++_elem;
			return (temp);
		};
		vector_iterator	&operator--(void)
		{
			--_elem;
			return (*this);
		};
		vector_iterator	operator--(int)
		{
			vector_iterator	temp(*this);
			--_elem;
			return (temp);
		};
		vector_iterator	operator+(difference_type n) const
		{
			vector_iterator	temp(*this);
			temp += n;
			return (temp);
		};
		vector_iterator	operator-(difference_type n) const
		{
			vector_iterator	temp(*this);
			temp -= n;
			return (temp);
		};
		reference		operator*(void) const
		{ return (*_elem); };
		pointer			operator->(void) const
		{ return (_elem); };
		reference		operator[](difference_type n) const
		{ return (*(_elem + n)); };

		// TypeCast overloading
		operator vector_iterator<const T> () const
		{ return (vector_iterator<const T>(this->_elem)); }
	};

	// Operator overloading
	template <class iter1, class iter2>
	bool	operator==(const ft::vector_iterator<iter1>& lhs, const ft::vector_iterator<iter2>& rhs)
	{ return (lhs.base() == rhs.base()); };
	template <typename T>
	bool	operator==(const ft::vector_iterator<T>& lhs, const ft::vector_iterator<T>& rhs)
	{ return (lhs.base() == rhs.base()); };

	template <class iter1, class iter2>
	bool	operator!=(const ft::vector_iterator<iter1>& lhs, const ft::vector_iterator<iter2>& rhs)
	{ return (lhs.base() != rhs.base()); };
	template <typename T>
	bool	operator!=(const ft::vector_iterator<T>& lhs, const ft::vector_iterator<T>& rhs)
	{ return (lhs.base() != rhs.base()); };

	template <class iter1, class iter2>
	bool	operator>(const ft::vector_iterator<iter1>& lhs, const ft::vector_iterator<iter2>& rhs)
	{ return (lhs.base() > rhs.base()); };
	template <typename T>
	bool	operator>(const ft::vector_iterator<T>& lhs, const ft::vector_iterator<T>& rhs)
	{ return (lhs.base() > rhs.base()); };

	template <class iter1, class iter2>
	bool	operator<(const ft::vector_iterator<iter1>& lhs, const ft::vector_iterator<iter2>& rhs)
	{ return (lhs.base() < rhs.base()); };
	template <typename T>
	bool	operator<(const ft::vector_iterator<T>& lhs, const ft::vector_iterator<T>& rhs)
	{ return (lhs.base() < rhs.base()); };

	template <class iter1, class iter2>
	bool	operator>=(const ft::vector_iterator<iter1>& lhs, const ft::vector_iterator<iter2>& rhs)
	{ return (lhs.base() >= rhs.base()); };
	template <typename T>
	bool	operator>=(const ft::vector_iterator<T>& lhs, const ft::vector_iterator<T>& rhs)
	{ return (lhs.base() >= rhs.base()); };

	template <class iter1, class iter2>
	bool	operator<=(const ft::vector_iterator<iter1>& lhs, const ft::vector_iterator<iter2>& rhs)
	{ return (lhs.base() <= rhs.base()); };
	template <typename T>
	bool	operator<=(const ft::vector_iterator<T>& lhs, const ft::vector_iterator<T>& rhs)
	{ return (lhs.base() <= rhs.base()); };

	template <typename T>
	typename ft::vector_iterator<T>
	operator+(typename ft::vector_iterator<T>::difference_type n, typename ft::vector_iterator<T>& rhs)
	{ return (rhs += n); };

	template <class iter1, class iter2>
	typename ft::vector_iterator<iter1>::difference_type
	operator-(const ft::vector_iterator<iter1>& lhs, const ft::vector_iterator<iter2>& rhs)
	{ return (lhs.base() - rhs.base()); };
	template <typename T>
	typename ft::vector_iterator<T>::difference_type
	operator-(const ft::vector_iterator<T>& lhs, const ft::vector_iterator<T>& rhs)
	{ return (lhs.base() - rhs.base()); };
}

#endif
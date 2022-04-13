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
		typedef ft::iterator<ft::random_access_iterator_tag, T>	iter;
		typedef iter::value_type								value_type;
		typedef iter::difference_type							difference_type;
		typedef iter::pointer									pointer;
		typedef iter::reference									reference;
		typedef iter::iterator_category							iterator_category;
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
		: _elem(origin._elem) {};
		virtual ~vector_iterator(void)
		{};

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
			++(*this);
			return (*this);
		};
		vector_iterator	&operator--(void)
		{
			--_elem;
			return (*this);
		};
		vector_iterator	operator--(int)
		{
			vector_iterator	temp(*this);
			--(*this);
			return (*this);
		};
		vector_iterator	operator+(difference_type n) const
		{
			vector_iterator	temp(*this);
			temp += n;
			return (temp);
		};
		vector_iterator	operator-(difference_type n) const
		{ return (*this + (-n)); };
		reference		operator*(void) const
		{ return (*_elem); };
		pointer			operator->(void) const
		{ return (&(*_elem)); };
		reference		operator[](difference_type n) const
		{ return (*(this + n)); };
	};

	// Operator overloading
	template <class iter1, class iter2>
	bool	operator==(const ft::vector_iterator<iter1>& lhs, const ft::vector_iterator<iter2>& rhs)
	{ return (*lhs == *rhs) };
	template <typename T>
	bool	operator==(const ft::vector_iterator<T>& lhs, const ft::vector_iterator<T>& rhs)
	{ return (*lhs == *rhs) };

	template <class iter1, class iter2>
	bool	operator!=(const ft::vector_iterator<iter1>& lhs, const ft::vector_iterator<iter2>& rhs)
	{ return (*lhs != *rhs) };
	template <typename T>
	bool	operator!=(const ft::vector_iterator<T>& lhs, const ft::vector_iterator<T>& rhs)
	{ return (*lhs != *rhs) };

	template <class iter1, class iter2>
	bool	operator>(const ft::vector_iterator<iter1>& lhs, const ft::vector_iterator<iter2>& rhs)
	{ return (*lhs > *rhs) };
	template <typename T>
	bool	operator>(const ft::vector_iterator<T>& lhs, const ft::vector_iterator<T>& rhs)
	{ return (*lhs > *rhs) };

	template <class iter1, class iter2>
	bool	operator<(const ft::vector_iterator<iter1>& lhs, const ft::vector_iterator<iter2>& rhs)
	{ return (*lhs < *rhs) };
	template <typename T>
	bool	operator<(const ft::vector_iterator<T>& lhs, const ft::vector_iterator<T>& rhs)
	{ return (*lhs < *rhs) };

	template <class iter1, class iter2>
	bool	operator>=(const ft::vector_iterator<iter1>& lhs, const ft::vector_iterator<iter2>& rhs)
	{ return (*lhs >= *rhs) };
	template <typename T>
	bool	operator>=(const ft::vector_iterator<T>& lhs, const ft::vector_iterator<T>& rhs)
	{ return (*lhs >= *rhs) };

	template <class iter1, class iter2>
	bool	operator<(const ft::vector_iterator<iter1>& lhs, const ft::vector_iterator<iter2>& rhs)
	{ return (*lhs <= *rhs) };
	template <typename T>
	bool	operator<(const ft::vector_iterator<T>& lhs, const ft::vector_iterator<T>& rhs)
	{ return (*lhs <= *rhs) };

	template <typename T>
	typename ft::vector_iterator<T>::difference_type
	operator+(typename ft::vector_iterator<T>::difference_type n, typename ft::vector_iterator<T>& rhs)
	{ return (n + &(*rhs)); };

	template <class iter1, class iter2>
	typename ft::vector_iterator<iter1>::difference_type
	operator-(const ft::vector_iterator<iter1>& lhs, const ft::vector_iterator<iter2>& rhs)
	{ return (*lhs - *rhs) };
	template <typename T>
	typename ft::vector_iterator<T>::difference_type
	operator-(const ft::vector_iterator<T>& lhs, const ft::vector_iterator<T>& rhs)
	{ return (*lhs - *rhs) };
}

#endif
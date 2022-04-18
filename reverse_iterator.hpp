#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "iterator.hpp"
# include "utils.hpp"

namespace ft
{
	template <class Iterator>
	class reverse_iterator
	: iterator<typename ft::iterator_traits<Iterator>::iterator_category
			, typename ft::iterator_traits<Iterator>::value_type
			, typename ft::iterator_traits<Iterator>::difference_type
			, typename ft::iterator_traits<Iterator>::pointer
			, typename ft::iterator_traits<Iterator>::reference>
	{
	public:
		// Typedef Member types
		typedef Iterator                                        			iterator_type;
		typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
		typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
		typedef typename ft::iterator_traits<Iterator>::reference			reference;
	private:
		// Element
		pointer _elem;
	public:
		reverse_iterator(void)
		: _elem(0) {};
		explicit reverse_iterator (iterator_type it
								, ft::enable_if<!ft::is_possible_RI<Iter>::value_type, Iter>::type isIter = Iter())
		: _elem(it) {};
		template <class Iter>
		reverse_iterator (const reverse_iterator<Iter>& rev_it
						, ft::enable_if<!ft::is_integral<Iter>::value_type, Iter>::type isIter = Iter())
		: _elem(rev_it.base()) {};
		template <Iter>
		reverse_iterator& operator=(const reverse_iterator<Iter>& origin)
		{
			if (this != &origin)
			{
				_elem = origin.base();
			}
			return (*this);
		}

		iterator_type	base() const {_elem};

		reference	operator*() const
		{
			iterator_type	it = _elem;
			return (*--it);
		};
		
		reverse_iterator	operator+(difference_type n) const
		{ return (reverse_iterator(_elem - n)); };

		reverse_iterator	operator-(difference_type n) const
		{ return (reverse_iterator(_elem + n)); };

		reverse_iterator& operator++()
		{
			--elem;
			return (*this)
		};
		reverse_iterator  operator++(int)
		{
			reverse_iterator	tmp(*this);
			--elem;
			return (tmp);
		};

		reverse_iterator& operator--()
		{
			++elem;
			return (*this);
		};
		reverse_iterator  operator--(int)
		{
			reverse_iterator	tmp(*this);
			++elem;
			return (tmp);
		};

		reverse_iterator&	operator+=(difference_type n)
		{
			_elem -= n;
			return (*this);
		};

		reverse_iterator&	operator-=(difference_type n)
		{
			_elem += n;
			return (*this);
		};

		reference operator[] (difference_type n) const
		{ return (*(*this + n)); };

		pointer	operator->() const
		{ return (&(*_elem)); };
	};

	template <class Iter>
	bool	operator==(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
	{ return (lhs.base() == rhs.base()); };
	template <class Iter>
	bool	operator!=(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
	{ return (lhs.base() != rhs.base()); };
	template <class Iter>
	bool	operator<(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
	{ return (lhs.base() < rhs.base()); };
	template <class Iter>
	bool	operator<=(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
	{ return (lhs.base() <= rhs.base()); };
	template <class Iter>
	bool	operator>(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
	{ return (lhs.base() > rhs.base()); };
	template <class Iter>
	bool	operator>=(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
	{ return (lhs.base() >= rhs.base()); };

	template <class Iter>
	reverse_iterator<Iter>	operator+
	(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& rev_it)
	{ return (reverse_iterator(rev_it.base() - n); };
	
	template <class Iter>
	typename reverse_iterator<Iter>::difference_type	operator-
	(const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
	{ return (lhs.base() - rhs.base()); };
};

#endif

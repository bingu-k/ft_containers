#ifndef	VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include "vector_iterator.hpp"

namespace ft
{
	template < class T, class Allocator = std::allocator<T> >
	class vector
	{
	public:
		typedef T											value_type;
		typedef Allocator									allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef ft::vector_iterator<T>						iterator;
		typedef ft::vector_iterator<const T>				const_iterator;
		// reverse_iterator
		// const_reverse_iterator
		typedef typename allocator_type::difference_type	difference_type;
		typedef typename allocator_type::size_type			size_type;

	private:
		allocator_type	_alloc;
		pointer			_begin;
		pointer			_end;
		pointer			_end_cap;

	public:
		// Constructor
		explicit vector (const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _begin(0), _end(0), _end_cap(0)
		{};
		explicit vector (size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _begin(0), _end(0), _end_cap(0)
		{
			_begin = _alloc.allocate(n);
			_end = _begin;
			_end_cap = _begin + n;
			while (n--)
			{
				_alloc.construct(_end, val);
				_end++;
			}
		};
		// iterator의 종류 확인해야하지 않을까?
		// 확인을 해야한다면 Random	Access Iterator만 받는게 말이 안되지않나.
		// 어차피 
		template <class InputIter>
		vector (InputIter first, InputIter last, const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _begin(0), _end(0), _end_cap(0)
		{
			difference_type	n = ft::distance(first, last);
			_begin = _alloc.allocate(n);
			_end = _begin;
			_end_cap = _begin + n;
			while (first != (last + 1))
			{
				_alloc.construct(_end, first);
				_end++;
				first++;
			}
		};
		vector (const vector& x);
	};
}
#endif
#ifndef	VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <iterator>

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
		// iterator
		// const_iterator
		// reverse_iterator
		// const_reverse_iterator
		typedef typename allocator_type::size_type			size_type;
		typedef typename allocator_type::difference_type	difference_type;

		explicit vector (const allocator_type& alloc = allocator_type());
		explicit vector (size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type());
		template <class InputIterator>
				vector (InputIterator first, InputIterator last,
						const allocator_type& alloc = allocator_type());
		vector (const vector& x);
	};
}
#endif
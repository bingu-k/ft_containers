#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <functional>
# include "pair.hpp"
# include "utils.hpp"
# include "iterator.hpp"

namespace ft
{
	template <class key, class T, class Compare = ft::less<key>, class Alloc = std::allocator<ft::pair<const key, T> > >
	class map
	{
	public:
		typedef key										key_type;
		typedef T										mapped_type;
		typedef ft::pair<const key_type, mapped_type>	value_type;
		typedef Compare									key_compare;
		class value_compare
		: public std::binary_function<value_type, value_type, bool>
		{
			friend class map;
		protected:
			key_compare	comp;
			value_compare (key_compare c) : comp(c) {};
		public:
			// typedef bool		result_type;
			// typedef value_type	first_argument_type;
			// typedef value_type	second_argument_type;
			bool	operator()(const value_type& x, const value_type& y) const
			{ return (comp(x.first, y.first)); };
		};

		typedef Alloc									allocator_type;
		typedef allocate_type::reference				reference;
		typedef allocate_type::const_reference			const_reference;
		typedef allocate_type::pointer					pointer;
		typedef allocate_type::const_pointer			const_pointer;

	private:
		typedef ft::pair<key_type, mapped_type>						_value_type;
		typedef ft::tree<value_type, value_compare, allocator_type>	base;

		base	_tree;

	public:
		// typedef map_iterator<typename base::iterator>				iterator;
		// typedef map_const_iterator<typename base::const_iterator>	const_iterator;
		// typedef ft::reverse_iterator<iterator>						reverse_iterator;
		// typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;
		// typedef iterator_traits<iterator>::size_type				size_type;
		// typedef iterator_traits<iterator>::difference_type			difference_type;
	};
}
#endif
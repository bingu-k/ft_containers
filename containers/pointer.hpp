#ifndef POINTER_HPP
# define POINTER_HPP

# include <cstddef>
# include "utils.hpp"

namespace ft
{
	template <class ptr>
	struct pointer_traits
	{
		typedef ptr													pointer;
		typedef typename pointer_traits_element_type<pointer>::type	element_type;
		typedef ptrdiff_t											difference_type;

		template <class U>
		struct rebind { typedef U* other; };
	};

	template <class T>
	struct pointer_traits<T*>
	{
		typedef T*			pointer;
		typedef T			element_type;
		typedef ptrdiff_t	difference_type;

		template <class U>
		struct rebind { typedef U* other; };
	};

};

#endif
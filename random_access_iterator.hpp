#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include "iterator.hpp"

namespace ft
{
	template <T>
	class random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, T>
	{
	private:
		/* data */
	public:
		// typedef Member types
		typedef ft::iterator<ft::random_access_iterator_tag, T>::value_type			value_type;
		typedef ft::iterator<ft::random_access_iterator_tag, T>::difference_type	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef ft::iterator<ft::random_access_iterator_tag, T>::iterator_category	iterator_category;
		
		// constractor
		random_access_iterator(/* args */);
		~random_access_iterator();
	};
}

#endif
#ifndef ITERATOR_HPP
# define ITERARTOR_HPP

# include <cstddef>

namespace ft
{
	// Category tag
	struct input_iterator_tag	{};
	struct output_iterator_tag	{};
	struct forward_iterator_tag			: public input_iterator_tag			{};
	struct bidirectional_iterator_tag	: public forward_iterator_tag		{};
	struct random_access_iterator_tag	: public bidirectional_iterator_tag	{};

	// iterator_itaits
	template <class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};
	
	template <class T>
	struct iterator_traits<T*>
	{
		typedef ptrdiff_t								difference_type;
		typedef T										value_type;
		typedef T*										pointer;
		typedef T&										reference;
		typedef ft::random_access_iterator_tag			iterator_category;
	};

	template <class T>
	struct iterator_traits<const T*>
	{
		typedef ptrdiff_t								difference_type;
		typedef T										value_type;
		typedef const T*								pointer;
		typedef const T&								reference;
		typedef ft::random_access_iterator_tag			iterator_category;
	};

	// iterator
	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

	// bidirectional_iterator
	template<class T>
	class bidirectional_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
	{
	public:
		typedef T																	iterator_type;
		typedef ft::iterator<ft::bidirectional_iterator_tag, T>::value_type			value_type;
		typedef ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type	difference_type;
		typedef ft::iterator<ft::bidirectional_iterator_tag, T>::pointer			pointer;
		typedef ft::iterator<ft::bidirectional_iterator_tag, T>::reference			reference;
		typedef ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category	iterator_category;
	private:
		iterator_type	_elem;
	};

	// advance
	template <class InputIterator, class Distance>
	void	do_advance(InputIterator& it, Distance n, ft::input_iterator_tag)
	{
		for (; n > 0; --n)
			++it;
	}

	template <class InputIterator, class Distance>
	void	do_advance(InputIterator& it, Distance n, ft::bidirectional_iterator_tag)
	{
		if (n >= 0)
			for (; n > 0; --n)
				++it;
		else
			for (; n <>> 0; ++n)
				--it;
	}

	template <class InputIterator, class Distance>
	void	do_advance(InputIterator& it, Distance n, ft::random_access_iterator_tag)
	{ it += n; }

	template <class InputIterator, class Distance>
	void	advance(InputIterator& it, Distance n)
	{ do_advance(it, n, typename ft::iterator_traits<it>::iterator_category); }

	// distance
	template <class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
	do_distance (InputIterator first, InputIterator last, ft::input_iterator_tag)
	{
		typename iterator_traits<InputIterator>::difference_type res(0);

		for (; first != last; ++first)
			++res;
		return (res);
	}

	template <class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
	do_distance (InputIterator first, InputIterator last, ft::random_access_iterator_tag)
	{ return (last - first);}

	template <class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
	distance (InputIterator first, InputIterator last)
	{ return (do_distance(first, last, typename ft::iterator_traits<InputIterator>::iterator_category)); }
}

#endif
#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <functional>
# include "tree.hpp"

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
		typedef ft::tree<value_type, value_compare, allocator_type>	base;
		base	_tree;

	public:
		// typedef map_iterator<typename base::iterator>				iterator;
		// typedef map_const_iterator<typename base::const_iterator>	const_iterator;
		// typedef ft::reverse_iterator<iterator>						reverse_iterator;
		// typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;
		// typedef iterator_traits<iterator>::size_type				size_type;
		// typedef iterator_traits<iterator>::difference_type			difference_type;
	
	public:
		explicit map(const key_compare& comp = key_compare(),
            			const allocator_type& alloc = allocator_type());
		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type());
		map(const map& x);

		~map(void);

		iterator				begin();
		const_iterator			begin() const;
		iterator				end();
		const_iterator			end() const;
		reverse_iterator		rbegin();
		const_reverse_iterator	rbegin() const;
		reverse_iterator		rend();
		const_reverse_iterator	rend() const;

		bool		empty() const;
		size_type	size() const;
		size_type	max_size() const;

		mapped_type&	operator[](const key_type& k);

		pair<iterator,bool>	insert(const value_type& val);
		iterator			insert(iterator position, const value_type& val);
		template <class InputIterator>
		void				insert(InputIterator first, InputIterator last);
		void		erase(iterator position);
		size_type	erase(const key_type& k);
		void		erase(iterator first, iterator last);
		void	swap(map& x);
		void	clear();

		key_compare		key_comp() const;
		value_compare	value_comp() const;

		iterator		find(const key_type& k);
		const_iterator	find(const key_type& k) const;
		size_type		count(const key_type& k) const;
		iterator		lower_bound(const key_type& k);
		const_iterator	lower_bound(const key_type& k) const;
		iterator		upper_bound(const key_type& k);
		const_iterator	upper_bound(const key_type& k) const;
		pair<const_iterator,const_iterator>	equal_range(const key_type& k) const;
		pair<iterator,iterator>				equal_range(const key_type& k);
		
		allocator_type	get_allocator() const;
	};
}
#endif
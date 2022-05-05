#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <functional>
# include "map_iterator.hpp"
# include "reverse_iterator.hpp"

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
		base			_tree;
		key_compare		_comp;
		allocator_type	_alloc;
	public:
		typedef map_iterator<typename base::iterator>				iterator;
		typedef map_const_iterator<typename base::const_iterator>	const_iterator;
		typedef ft::reverse_iterator<iterator>						reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;
		typedef iterator_traits<iterator>::size_type				size_type;
		typedef iterator_traits<iterator>::difference_type			difference_type;
	
	public:
		explicit map(const key_compare& comp = key_compare(),
            			const allocator_type& alloc = allocator_type())
		: _tree(), _comp(comp), _alloc(alloc) {};
		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type());
		: _tree(), _comp(comp), _alloc(alloc)
		{
			_tree.insert_multi(first, last);
		};
		map(const map& x);

		~map(void);

		iterator				begin() { return (_tree.begin()); };
		const_iterator			begin() const { return (_tree.begin()); };
		iterator				end() { return (_tree.end()); };
		const_iterator			end() const { return (_tree.end()); };
		reverse_iterator		rbegin() { return (_tree.end()); };
		const_reverse_iterator	rbegin() const { return (_tree.end()); };
		reverse_iterator		rend() { return (_tree.begin()); };
		const_reverse_iterator	rend() const { return (_tree.begin()); };

		bool		empty() const { return (_tree.size() == 0); };
		size_type	size() const { return (_tree.size()); };
		size_type	max_size() const{ return (_tree.max_size()); };;

		mapped_type&	operator[](const key_type& k) { return (_tree.find(k)->second); };

		pair<iterator,bool>	insert(const value_type& val)
		{ return (_tree.insert_unique(val)); };
		iterator			insert(iterator position, const value_type& val)
		{ return (_tree.insert_unique(position, val))};
		template <class InputIter>
		void				insert(InputIter first, InputIter last)
		{ return (_tree.insert_multi(first, last)); };
		void		erase(iterator position)
		{ _tree.erase_unique_iter(position); };
		size_type	erase(const key_type& k)
		{
			_tree.erase_unique(key_type);
			return (1);
		};
		void		erase(iterator first, iterator last)
		{ _tree.erase_multi(first, last)};
		void	swap(map& x) { _tree.swap(); };
		void	clear(void) { _tree.all_clear() };

		key_compare		key_comp() const { return (key_compare()); };
		value_compare	value_comp() const { return (value_compare(key_compare())); };

		iterator		find(const key_type& k) { return (_tree.find(k)); };
		const_iterator	find(const key_type& k) const { return (_tree.find(k)); };
		size_type		count(const key_type& k) const;
		iterator		lower_bound(const key_type& k) { return (_tree.lower_bound(k)); };
		const_iterator	lower_bound(const key_type& k) const { return (_tree.lower_bound(k)); };
		iterator		upper_bound(const key_type& k) { return (_tree.lower_bound(k)); };
		const_iterator	upper_bound(const key_type& k) const { return (_tree.lower_bound(k)); };
		pair<const_iterator,const_iterator>	equal_range(const key_type& k) const
		{ return (ft::pair(lower_bound(k), upper_bound(k))); };
		pair<iterator,iterator>				equal_range(const key_type& k)
		{ return (ft::pair(lower_bound(k), upper_bound(k))); };
		
		allocator_type	get_allocator() const { return (this->_alloc); };
	};
}
#endif
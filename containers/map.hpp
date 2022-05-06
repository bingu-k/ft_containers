#ifndef MAP_HPP
# define MAP_HPP

# include "iterator.hpp"
# include "tree.hpp"

namespace ft
{
	template <class Key, class T, class Compare = ft::less<Key>
			, class Alloc = std::allocator<pair<const Key, T> > >
	class map
	{
	public:
		//Type Define
		typedef Key												key_type;	// key
		typedef T												mapped_type;// value
		typedef ft::pair<const key_type, mapped_type>			value_type;	// pair
		typedef Compare											key_compare;
		class value_compare									//value_compare
		: public std::binary_function<value_type, value_type, bool>
		{
			template <class, class, class, class> friend class map
		protected:
			key_compare	comp;
			value_compare(key_compare c) : comp(c) {};
		public:
			bool	operator()(const value_type& x, const value_type& y) const
			{ return (comp(x.first, y.first)); };
		};
		typedef Alloc											allocator_type;
		typedef typename allocator_type::reference				reference;
		typedef typename allocator_type::const_reference		const_reference;
		typedef typename allocator_type::pointer				pointer;
		typedef typename allocator_type::const_pointer			const_pointer;
		typedef typename allocator_type::size_type				size_type;
	private:
		typedef tree<value_type, _value_compare<key_type, value_type, key_compare>
							, allocator_type>					base;
		value_compare	_comp;
		allocator_type	_alloc;
		base			_tree;
		base&			get_tree(void) { return (this->_tree); };
	public:
		typedef map_iterator<typename base::iterator, value_type>
																iterator;
		typedef map_iterator<typename base::const_iterator, value_type>
																const_iterator;
		typedef reverse_iterator<iterator>						reverse_iterator;
		typedef reverse_iterator<const_iterator>				const_reverse_iterator;
		typedef typename iterator_traits<iterator>::difference_type
																difference_type;

		// Constructor
		explicit map(const key_compare& comp = key_compare()
					, const allocator_type& alloc = allocator_type())
		: _comp(value_compare(comp)), _alloc(alloc) {};
		template <class InputIterator>
		map(InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type())
		: _comp(value_compare(comp)), _alloc(alloc) {};
		map(const map& x)
		: _comp(x.value_comp()), _alloc(x.get_allocator()) {};

		// Copy Constructor
		map&	operator=(const map& x)
		{
			if (this == &x)
			{
				this->_comp = x.value_comp();
				this->_alloc = x.get_alloc();
			}
			return (*this);
		};

		// Distructor
		~map(void) { clear(); };

		// Iterators
		iterator		begin()			{ return (iterator(_tree.begin())); };
		const_iterator	begin() const	{ return (iterator(_tree.begin())); };
		iterator		end()			{ return (iterator(_tree.end())); };
		const_iterator	end() const		{ return (iterator(_tree.end())); };
		reverse_iterator		rbegin()		{ return (iterator(_tree.end())); };
		const_reverse_iterator	rbegin() const	{ return (iterator(_tree.end())); };
		reverse_iterator		rend()			{ return (iterator(_tree.begin())); };
		const_reverse_iterator	rend() const	{ return (iterator(_tree.begin())); };

		// Capacity
		bool		empty() const		{ return (this->size() == 0); };
		size_type	size() const		{ return (_tree.size()); };
		size_type	max_size() const	{ return (_tree.max_size()); };

		// Element Access
		mapped_type&	operator[](const key_type& k) { return (_tree.find(k).second); };

		// Modifiers
		pair<iterator,bool>	insert(const value_type& val)
		{
			value_type	res_type = _tree.insert_unique(val);
			if (res_type != val)
				return (ft::pair(iterator(res_type, false)));
			else
				return (ft::pair(iterator(res_type, true));
		};
		iterator			insert(iterator position, const value_type& val)
		{ return (iterator(_tree.insert_pos(position.get_tree_iter(), val))); };
		template <class InputIterator>
		void				insert(InputIterator first, InputIterator last)
		{ _tree.insert_multi(first.get_tree_iter(), last.get_tree_iter()); };
		void		erase(iterator position)
		{ _tree.remove_pos(position.get_tree_iter()); };
		size_type	erase(const key_type& k)
		{
			_tree.remove_unique(k);
			return (1);
		};
		void		erase(iterator first, iterator last)
		{ _tree.remove_multi(first.get_tree_iter(), last.get_tree_iter()); };
		void	swap(map& x)
		{
			swap_something(this->_alloc, x.get_allocator());
			swap_something(this->_comp, x.value_comp());
			this->_tree.swap(x.get_tree());
		};
		void	clear() { _tree.all_clear(); };

		// Observers
		key_compare		key_comp() const	{ return (key_compare()); };
		value_compare	value_comp() const	{ return (this->_comp); };

		// Operations
		iterator		find(const key_type& k)
		{ return (iterator(_tree.find(k))); };
		const_iterator	find(const key_type& k) const
		{ return (const_iterator(_tree.find(k))); };
		size_type	count(const key_type& k) const
		{
			if (_tree.find(k) == m_nullptr)
				return (0);
			else
				return (1);
		};
		iterator		lower_bound(const key_type& k)
		{ return (iterator(_tree.lower_bound(k))); };
		const_iterator	lower_bound(const key_type& k) const
		{ return (iterator(_tree.lower_bound(k))); };
		iterator		upper_bound(const key_type& k)
		{ return (iterator(_tree.upper_bound(k))); };
		const_iterator	upper_bound(const key_type& k) const
		{ return (iterator(_tree.upper_bound(k))); };
		pair<iterator,iterator>				equal_range(const key_type& k)
		{
			iterator	first = lower_bound(k);
			iterator	second = upper_bound(k);
			return (ft::pair(first, second));
		};
		pair<const_iterator,const_iterator>	equal_range(const key_type& k) const
		{
			const_iterator	first = lower_bound(k);
			const_iterator	second = upper_bound(k);
			return (ft::pair(first, second));
		};

		// Allocator
		allocator_type	get_allocator() const	{ return (this->_alloc); };
	};
}

#endif
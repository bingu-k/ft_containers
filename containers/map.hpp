#ifndef MAP_HPP
# define MAP_HPP

# include "tree.hpp"
# include "reverse_iterator.hpp"

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
			template <class, class, class, class> friend class map;
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
		typedef _value_compare<key_type, value_type, key_compare>
																_vc;
		typedef tree<value_type, _vc, allocator_type>			base;
		typedef typename base::iterator							tree_iter;
		typedef typename base::const_iterator					const_tree_iter;
		allocator_type	_alloc;
		base			_tree;
	public:
		typedef map_iterator<tree_iter, value_type>				iterator;
		typedef map_const_iterator<const_tree_iter, value_type>	const_iterator;
		typedef ft::reverse_iterator<iterator>					reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
		typedef typename iterator_traits<iterator>::difference_type
																difference_type;

		// Constructor
		explicit map(const key_compare& comp = key_compare()
					, const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _tree(comp, alloc)
		{};
		template <class InputIterator>
		map(InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _tree(comp, alloc)
		{ this->insert(first, last); };
		map(const map& x)
		: _alloc(x.get_allocator()), _tree(x._tree)
		{};

		// Copy Constructor
		map&	operator=(const map& x)
		{
			if (this != &x)
			{
				this->_alloc = x._alloc;
				this->_tree = x._tree;
			}
			return (*this);
		};

		// Distructor
		~map(void) {};

		// Iterators
		iterator		begin()			{ return (iterator(_tree.begin())); };
		const_iterator	begin() const	{ return (const_iterator(_tree.begin())); };
		iterator		end()			{ return (iterator(_tree.end())); };
		const_iterator	end() const		{ return (const_iterator(_tree.end())); };
		reverse_iterator		rbegin()		{ return (reverse_iterator(_tree.end())); };
		const_reverse_iterator	rbegin() const	{ return (const_reverse_iterator(_tree.end())); };
		reverse_iterator		rend()			{ return (reverse_iterator(_tree.begin())); };
		const_reverse_iterator	rend() const	{ return (const_reverse_iterator(_tree.begin())); };

		// Capacity
		bool		empty() const		{ return (this->size() == 0); };
		size_type	size() const		{ return (_tree.size()); };
		size_type	max_size() const	{ return (_tree.max_size()); };
		base		get_tree(void) const { return (this->_tree); };

		// Element Access
		mapped_type&	operator[](const key_type& k)
		{
			iterator	check = find(k);
			if (check == this->end())
			{
				iterator	res(this->_tree.insert_unique(ft::make_pair(k, mapped_type())).first);
				return ((*res).second);
			}
			return ((*check).second);
		};

		// Modifiers
		pair<iterator, bool>	insert(const value_type& val)
		{
			pair<tree_iter, bool>	res_type = _tree.insert_unique(val);
			return (ft::pair<iterator,bool>(iterator(res_type.first), res_type.second));
		};
		iterator			insert(iterator position, const value_type& val)
		{ return (iterator(_tree.insert_pos(position.get_tree_iter(), val))); };
		template <class InputIterator>
		void				insert(InputIterator first, InputIterator last)
		{ _tree.insert_multi(first, last); };
		void		erase(iterator position)
		{ _tree.remove_pos(position.get_tree_iter()); };
		size_type	erase(const key_type& k)
		{ return (_tree.remove_unique(k)); };
		void		erase(iterator first, iterator last)
		{ _tree.remove_multi(first.get_tree_iter(), last.get_tree_iter()); };
		void	swap(map& x)
		{
			this->_tree.swap(x._tree);
			ft::swap_something(this->_alloc, x._alloc);
		};
		void	clear()	{ _tree.all_clear(); };

		// Observers
		key_compare		key_comp() const	{ return (key_compare()); };
		value_compare	value_comp() const	{ return (value_compare(key_compare())); };

		// Operations
		iterator		find(const key_type& k)
		{ return (iterator(_tree.find(k))); };
		const_iterator	find(const key_type& k) const
		{ return (const_iterator(_tree.find(k))); };
		size_type	count(const key_type& k) const
		{ return (_tree.count(k)); };
		iterator		lower_bound(const key_type& k)
		{ return (iterator(_tree.lower_bound(k))); };
		const_iterator	lower_bound(const key_type& k) const
		{ return (const_iterator(_tree.lower_bound(k))); };
		iterator		upper_bound(const key_type& k)
		{ return (iterator(_tree.upper_bound(k))); };
		const_iterator	upper_bound(const key_type& k) const
		{ return (const_iterator(_tree.upper_bound(k))); };
		pair<iterator,iterator>				equal_range(const key_type& k)
		{
			iterator	first = lower_bound(k);
			iterator	second = upper_bound(k);
			return (make_pair(first, second));
		};
		pair<const_iterator,const_iterator>	equal_range(const key_type& k) const
		{
			const_iterator	first = _tree.lower_bound(k);
			const_iterator	second = _tree.upper_bound(k);
			return (make_pair(first, second));
		};

		// Allocator
		allocator_type	get_allocator() const	{ return (this->_alloc); };

		// order
		void	printMap(void)
		{
			std::cout << "\tInorder Map" << std::endl;
			_tree.inorder(_tree.root());
			std::cout << "\tPreorder Map" << std::endl;
			_tree.preorder(_tree.root());
		};
	};
	// Relational Operators
	template <class Key, class T, class Compare, class Alloc>
	bool	operator==(const map<Key,T,Compare,Alloc>& lhs
					, const map<Key,T,Compare,Alloc>& rhs )
	{ return (ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); };

	template <class Key, class T, class Compare, class Alloc>
	bool	operator!=(const map<Key,T,Compare,Alloc>& lhs
					, const map<Key,T,Compare,Alloc>& rhs )
	{ return (!(lhs == rhs)); };

	template <class Key, class T, class Compare, class Alloc>
	bool	operator<(const map<Key,T,Compare,Alloc>& lhs
					, const map<Key,T,Compare,Alloc>& rhs )
	{ return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); };

	template <class Key,class T, class Compare, class Alloc>
	bool	operator<=(const map<Key,T,Compare,Alloc>& lhs
					, const map<Key,T,Compare,Alloc>& rhs )
	{ return (!(lhs > rhs)); };

	template <class Key, class T, class Compare, class Alloc>
	bool	operator>(const map<Key,T,Compare,Alloc>& lhs
					, const map<Key,T,Compare,Alloc>& rhs )
	{ return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end())); };

	template <class Key, class T, class Compare, class Alloc>
	bool	operator>=(const map<Key,T,Compare,Alloc>& lhs
					, const map<Key,T,Compare,Alloc>& rhs )
	{ return (!(lhs < rhs)); };

	template <class Key, class T, class Compare, class Alloc>
	void	swap(const map<Key,T,Compare,Alloc>& lhs
					, const map<Key,T,Compare,Alloc>& rhs )
	{ lhs.swap(rhs); };
}

#endif
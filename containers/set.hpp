#ifndef SET_HPP
# define SET_HPP

/*
namespace ft
{
	template <class Key, class Compare = ft::less<Key>
			, class Allocator = std::allocator<Key> >
	class set
	{
	public:
		typedef Key											key_type;
		typedef key_type									value_type;
		typedef Compare										key_compare;
		typedef key_compare									value_compare;
		typedef Allocator									allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
	private:
		typedef tree<key_type, value_type, value_compare, allocator_type>
															base;
		base	tree;
	public:
		typedef typename base::iterator						iterator;
		typedef typename base::const_iterator				const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
		typedef typename base::difference_type				difference_type;
		typedef typename base::size_type					size_type;
	public:
	public:
		explicit set(const key_compare& comp = key_compare()
					, const allocator_type& alloc = allocator_type());
		template <class InputIterator>
		set(InputIterator first, InputIterator last
			, const key_compare& comp = key_compare(),
			, const allocator_type& alloc = allocator_type());
		set(const set& x);
		set&	operator=(const set& x);
		~set(void);

		// Iterator
		iterator		begin();
		const_iterator	begin() const;
		iterator		end();
		const_iterator	end() const;
		reverse_iterator		rbegin();
		const_reverse_iterator	rbegin() const;
		reverse_iterator		rend();
		const_reverse_iterator	rend() const;

		// Capacity
		bool		empty() const;
		size_type	size() const;
		size_type	max_size() const;

		// Modifiers
		pair<iterator,bool>	insert(const value_type& val);
		iterator			insert(iterator position, const value_type& val);
		template <class InputIterator>
		void				insert(InputIterator first, InputIterator last);
		void		erase(iterator position);
		size_type	erase(const value_type& val);
		void		erase(iterator first, iterator last);
		void	swap(set& x);
		void	clear(void);

		// Observers
		key_compare		key_comp() const;
		value_compare	value_comp() const;

		// Operations
		iterator	find(const value_type& val) const;
		size_type	count(const value_type& val) const;
		iterator	lower_bound(const value_type& val) const;
		iterator	upper_bound(const value_type& val) const;
		pair<iterator,iterator>	equal_range(const value_type& val) const;

		// Allocator
		allocator_type	get_allocator() const;
	};
}
*/


# include "utils.hpp"
# include "tree.hpp"
# include "reverse_iterator.hpp"

namespace ft
{
	template <class Key, class Compare = ft::less<Key>
			, class Allocator = std::allocator<Key> >
	class set
	{
	public:
		typedef const Key									key_type;
		typedef key_type									value_type;
		typedef Compare										key_compare;
		typedef key_compare									value_compare;
		typedef Allocator									allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
	private:
		typedef tree<value_type, value_compare, allocator_type>
															base;
		allocator_type	_alloc;
		base			_tree;
	public:
		typedef typename base::difference_type				difference_type;
		typedef typename base::size_type					size_type;
		typedef typename base::iterator						iterator;
		typedef typename base::const_iterator				const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
	public:
		explicit set(const key_compare& comp = key_compare()
					, const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _tree(comp, alloc) {};
		template <class InputIterator>
		set(InputIterator first, InputIterator last
			, const key_compare& comp = key_compare()
			, const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _tree(comp, alloc)
		{ this->insert(first, last); };
		set(const set& x)
		: _alloc(x.get_allocator()), _tree(x._tree) {};
		set&	operator=(const set& x)
		{
			if (this != &x)
			{
				this->_alloc = x._alloc;
				this->_tree = x._tree;
			}
			return (*this);
		};
		~set(void) {};

		// Iterator
		iterator		begin()					{ return (_tree.begin()); };
		const_iterator	begin() const			{ return (_tree.begin()); };
		iterator		end()					{ return (_tree.end()); };
		const_iterator	end() const				{ return (_tree.end()); };
		reverse_iterator		rbegin()		{ return (reverse_iterator(_tree.end())); };
		const_reverse_iterator	rbegin() const	{ return (const_reverse_iterator(_tree.end())); };
		reverse_iterator		rend()			{ return (reverse_iterator(_tree.begin())); };
		const_reverse_iterator	rend() const	{ return (const_reverse_iterator(_tree.begin())); };

		// Capacity
		bool		empty() const { return(this->size() == 0); };
		size_type	size() const { return (this->_tree.size()); };
		size_type	max_size() const { return (this->_tree.max_size()); };

		// Modifiers
		pair<iterator,bool>	insert(const value_type& val)
		{ return (this->_tree.insert_unique(val)); };
		iterator			insert(iterator position, const value_type& val)
		{ return (this->_tree.insert_pos(position, val)); };
		template <class InputIterator>
		void				insert(InputIterator first, InputIterator last)
		{ this->_tree.insert_multi(first, last); };
		void		erase(iterator position)
		{ this->_tree.remove_pos(position); };
		size_type	erase(const value_type& val)
		{ return (this->_tree.remove_unique(val)); };
		void		erase(iterator first, iterator last)
		{ this->_tree.remove_multi(first, last); };
		void	swap(set& x)
		{ this->_tree.swap(x._tree); };
		void	clear(void)
		{ this->_tree.all_clear(); };

		// Observers
		key_compare		key_comp() const	{ return (key_compare()); };
		value_compare	value_comp() const	{ return (value_compare()); };

		// Operations
		iterator		find(const value_type& val)
		{ return (this->_tree.find(val)); };
		const_iterator	find(const value_type& val) const
		{ return (this->_tree.find(val)); };
		size_type	count(const value_type& val) const
		{ return (this->_tree.count(val)); };
		iterator		lower_bound(const value_type& val)
		{ return (this->_tree.lower_bound(val)); };
		const_iterator	lower_bound(const value_type& val) const
		{ return (this->_tree.lower_bound(val)); };
		iterator		upper_bound(const value_type& val)
		{ return (this->_tree.upper_bound(val)); };
		const_iterator	upper_bound(const value_type& val) const
		{ return (this->_tree.upper_bound(val)); };
		pair<iterator,iterator>				equal_range(const value_type& val)
		{
			iterator	first = lower_bound(val);
			iterator	second = upper_bound(val);
			return (make_pair(first, second));
		}
		pair<const_iterator,const_iterator>	equal_range(const value_type& val) const
		{
			const_iterator	first = lower_bound(val);
			const_iterator	second = upper_bound(val);
			return (make_pair(first, second));
		}

		// Allocator
		allocator_type	get_allocator() const
		{ return (this->_alloc); };
	};
	// Relational Operators
	template <class T, class Compare, class Alloc>
	bool	operator==(const set<T,Compare,Alloc>& lhs
					, const set<T,Compare,Alloc>& rhs)
	{ return (lhs.size() == rhs.size()
			&& ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); };

	template <class T, class Compare, class Alloc>
	bool	operator!=(const set<T,Compare,Alloc>& lhs
					, const set<T,Compare,Alloc>& rhs)
	{ return (!(lhs == rhs)); };

	template <class T, class Compare, class Alloc>
	bool	operator<(const set<T,Compare,Alloc>& lhs
					, const set<T,Compare,Alloc>& rhs)
	{ return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); };

	template <class T, class Compare, class Alloc>
	bool	operator<=(const set<T,Compare,Alloc>& lhs
					, const set<T,Compare,Alloc>& rhs)
	{ return (!(lhs > rhs)); };

	template <class T, class Compare, class Alloc>
	bool	operator>(const set<T,Compare,Alloc>& lhs
					, const set<T,Compare,Alloc>& rhs)
	{ return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end())); };

	template <class T, class Compare, class Alloc>
	bool	operator>=(const set<T,Compare,Alloc>& lhs
					, const set<T,Compare,Alloc>& rhs)
	{ return (!(lhs < rhs)); };
}

#endif
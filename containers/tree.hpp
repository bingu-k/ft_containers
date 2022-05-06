#ifndef TREE_HPP
# define TREE_HPP

# include "utils.hpp"
# include "iterator.hpp"
# include "map_iterator.hpp"

namespace ft
{
	template <class Value, class Compare, class Alloc>
	class tree
	{
	public:
		// Type Define
		typedef	Value											value_type;
		typedef Compare											value_compare;
		typedef Alloc											allocator_type;
		typedef typename allocator_type::template rebind<node<value_type> >::other
																node_allocator_type;
		typedef typename node_allocator_type::size_type			size_type;
		typedef node<value_type>*								nodeptr;
		typedef tree_iterator<nodeptr, value_type>				iterator;
		typedef tree_const_iterator<nodeptr, value_type>		const_iterator;
		typedef typename iterator::difference_type				difference_type;

	private:
		size_type			_size;
		nodeptr				_root;
		nodeptr				_nil;
		node_allocator_type	_alloc;
		value_compare		_comp;
	public:
		tree(allocator_type alloc = node_allocator_type(), value_compare comp = value_compare())
		: _size(0), _root(m_nullptr), _nil(m_nullptr), _alloc(alloc), _comp(comp)
		{
			this->_nil = _alloc.allocate(node<value_type>(), 1);
			_alloc.construct(this->_nil, node<value_type>());
			this->_nil->_color = Black;
			this->_root = this->_nil;
		};
		tree(const tree& x)
		: _size(0), _root(x.root()), _nil(x.nil()), _alloc(x.alloc()), _comp(x.comp())
		{};
		~tree() { all_clear(); };

		// GETTER
		size_type			size(void) const { return (this->_size); };
		nodeptr				root(void) const { return (this->_root); };
		nodeptr				nil(void) const { return (this->_nil); };
		node_allocator_type	alloc(void) const { return (this->_alloc); };
		value_compare		comp(void) const { return (this->_comp); };

		// Iterators
		iterator		begin() { };
		const_iterator	begin() const;
		iterator		end();
		const_iterator	end() const;

		// Capacity
		bool		empty() const		{ return (this->size() == 0); };
		size_type	max_size() const	{ return (this->_alloc.max_size()); };

		// Modifiers
		value_type	insert_unique(const value_type& val) {};
		iterator	insert_pos(iterator	pos, const value_type& val) {};
		template <class InputIter>
		void		insert_multi(InputIter first, InputIter last) {};
		void		remove_unique(const key_type& k) {};
		void		remove_pos(itereator pos) {};
		void		remove_unique(iterator first, iterator last) {};
		void		swap(tree& x)
		{
			swap_something(this->size(), x.size());
			swap_something(this->root(), x.root());
			swap_something(this->nil(), x.nil());
			swap_something(this->alloc(), x.alloc());
			swap_something(this->comp(), x.comp());
		}
	};
}

#endif
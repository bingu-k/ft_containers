#ifndef TREE_HPP
# define TREE_HPP

# include "iterator.hpp"
# include "utils.hpp"
# include "pair.hpp"

namespace ft
{
	/////////////////////// node ///////////////////////
	typedef enum
	{
		Red,
		Black
	} node_color;

	template <class M>
	struct val_node
	{
		typedef M		mapped_type;

		mapped_type		_val;

		val_node(mapped_type _val = m_nullptr) : _val(_val)
		{};
	};

	template <class V, class M>
	struct node : public val_node<M>
	{
		typedef node*	nodeptr;
		typedef V		value_type;
		typedef M		mapped_type;

		value_type	_value;
		node_color	_color;
		nodeptr		_parent;
		nodeptr		_left;
		nodeptr		_right;

		node(void) : val_node<mapped_type>(), _value(m_nullptr), _color(Red)
		, _parent(m_nullptr), _left(m_nullptr), _right(m_nullptr)
		{}
		node(const value_type& key, const mapped_type& val)
		: val_node<mapped_type>(val), _value(key), _color(Red)
		, _parent(m_nullptr), _left(m_nullptr), _right(m_nullptr)
	};

	/////////////////////// iter ///////////////////////

	template <class T, class nodeptr>
	class tree_iterator
	{
	public:
		// Typedef Memder types
		typedef	T													value_type;
		typedef nodeptr												iterator_type;
		typedef ft::iterator<bidirectional_iterator_tag(), nodeptr>	iter;
		typedef typename iter::value_type							value_type;
		typedef typename iter::difference_type						difference_type;
		typedef iterator_type										pointer;
		typedef value_type&											reference;
		typedef typename iter::iterator_category					iterator_category;
	private:
		// Element
		pointer	_elem;
	public:
		tree_iterator(void) : _elem(m_nullptr) {};
		tree_iterator(pointer elem) : _elem(elem)) {};
		tree_iterator(const tree_iterator& origin)
		: _elem(origin._elem) {};
		tree_iterator&	operator=(const tree_iterator& origin)
		{
			if (this != &origin)
				this->_elem = origin._elem;
			return (*this);
		}

		reference		operator*() const
		{ return (this->_elem->_value); };
		pointer			operator->() const
		{ return &(this->_elem->_value); };
		tree_iterator	operator++()
		{
			tree_iterator	temp(*this);
			++(*this);
			return (temp);
		};
		tree_iterator	operator++(int)
		{
			this->_elem = tree_next_iterator<iterator_type>(this->_elem);
			return (*this);
		};
		tree_iterator	operator--()
		{
			tree_iterator	temp(*this);
			--(*this);
			return (temp);
		};
		tree_iterator	operator--(int)
		{
			this->_elem = tree_prev_iterator(this->_elem);
			return (*this);
		};
		bool			operator==(const tree_iterator& x, const tree_iterator& y)
		{ return (x._elem == y._elem); };
		bool			operator!=(const tree_iterator& x, const tree_iterator& y)
		{ return !(x == y); };
	};

	template <class T, class nodeptr>
	class tree_const_iterator
	{
	public:
		// Typedef Memder types
		typedef	T													value_type;
		typedef nodeptr												iterator_type;
		typedef ft::iterator<bidirectional_iterator_tag(), nodeptr>	iter;
		typedef typename iter::value_type							value_type;
		typedef typename iter::difference_type						difference_type;
		typedef const nodeptr										pointer;
		typedef value_type&											reference;
		typedef typename iter::iterator_category					iterator_category;

	private:
		typedef tree_iterator<value_type, iterator_type>			non_const_iter;
		// Element
		pointer	_elem;
	public:
		tree_const_iterator(void) : _elem(m_nullptr) {};
		tree_const_iterator(pointer elem) : _elem(elem)) {};
		tree_const_iterator(const tree_const_iterator& origin)
		: _elem(origin._elem) {};
		tree_const_iterator(non_const_iter p)
		: _elem(p._elem) {};
		
		reference		operator*() const
		{ return (this->_elem->_value); };
		pointer			operator->() const
		{ return &(this->_elem->_value); };
		tree_const_iterator	operator++()
		{
			tree_const_iterator	temp(*this);
			++(*this);
			return (temp);
		};
		tree_const_iterator	operator++(int)
		{
			this->_elem = tree_next_iterator(this->_elem);
			return (*this);
		};
		tree_const_iterator	operator--()
		{
			tree_const_iterator	temp(*this);
			--(*this);
			return (temp);
		};
		tree_const_iterator	operator--(int)
		{
			this->_elem = tree_prev_iterator(this->_elem);
			return (*this);
		};
		bool			operator==(const tree_const_iterator& x, const tree_const_iterator& y)
		{ return (x._elem == y._elem); };
		bool			operator!=(const tree_const_iterator& x, const tree_const_iterator& y)
		{ return !(x == y); };
	};

	template <class nodeptr>
	inline nodeptr	tree_next_iterator(nodeptr curr_node)
	{
		if (curr_node->_right != m_nullptr)
		{
			curr_node = curr_node->_right;
			while (curr_node->_left != m_nullptr)
				curr_node = curr_node->_left;
			return (curr_node);
		}
		while (curr_node->_parent->_left != curr_node)
			curr_node = curr_node->_parent;
		return (curr_node->_parent);
	};

	template <class nodeptr>
	inline nodeptr	tree_prev_iterator(nodeptr curr_node)
	{
		if (curr_node->_left != m_nullptr)
		{
			curr_node = curr_node->_left;
			while (curr_node->_right != m_nullptr)
				curr_node = curr_node->_right;
			return (curr_node);
		}
		while (curr_node->_parent->_right != curr_node)
			curr_node = curr_node->_parent;
		return (curr_node->_parent);
	}

	/////////////////////// tree ///////////////////////
	template <class V, class Compare, class Alloc>
	class tree
	{
	public:
		typedef V											value_type;
		typedef Compare										value_compare;
		typedef typename value_type::first_type				key_type;
		typedef typename value_type::second_type			mapped_type;

		typedef	value_type*									pointer;
		typedef const value_type*							const_pointer;
		typedef value_type&									reference;
		typedef const value_type&							const_reference;

		typedef node<value_type, mapped_type>				non_ptr_node;
		typedef node<value_type, mapped_type>*				nodeptr;
		typedef Alloc										allocator_type;
		typedef typename Alloc::template rebind<non_ptr_node>::other
															node_alloc;
		typedef typename node_alloc::difference_type		difference_type;
		typedef typename node_alloc::size_type				size_type;

		typedef tree_iterator<value_type, nodeptr>			iterator;
		typedef tree_const_iterator<value_type, nodeptr>	const_iterator;

	private:
		size_type	_size;
		nodeptr		_root;
		nodeptr		_nil;
		node_alloc	_alloc;
	public:
		tree(allocator alloc = node_alloc())
		: _size(0), _root(m_nullptr), _nil(m_nullptr), _alloc(alloc)
		{
			this->_nil = _alloc.allocate(1);
			_alloc.construct(this->_nil, non_ptr_node());
			this->_nil->_color = Black;
			this->_root = this->_nil;
		}
		virtual ~tree(void)
		{
			all_clear(_root);
			remove_node(_nil);
		};

	// Red-Black Tree
		// Utility
	private:
		nodeptr	find_bro_node(nodeptr target_node) const
		{
			if (target_node == _root)
				return (m_nullptr);
			else if (target_node == target_node->_parent->_left)
				return (target_node->_parent->_right);
			else
				return (target_node->_parent->_left);
		};
		nodeptr	find_replace_node(nodeptr replace_node)
		{
			if (replace_node->_left == _nil)
				return (replace_node->_right);
			else if (replace_node->_right == _nil)
				return (replace_node->_left);
			else
			{
				replace_node = replace_node->_right;
				while (replace_node->_left != _nil
					&& replace_node->_left != m_nullptr)
					replace_node = replace_node->_left;
				return (replace_node);
			}
		};
		void	replace(nodeptr target_node, nodeptr replace_node);
		void	insert_fixup(nodeptr target_node);
		void	delete_fixup(nodeptr target_node);
		void	remove_node(nodeptr target_node);
		void	all_clear(nodeptr node);
		void	left_rotation(nodeptr x);
		void	right_rotation(nodeptr y);
	public:
		nodeptr	insert_node(nodeptr target_node, nodeptr criteria_node = _root));
		void	delete_node(nodeptr target_node);

	///////////////// map relative function /////////////////
	public:
		size_type	size(void) { return (this->_size); };
		size_type	max_size(void) { return (this->_alloc.max_size()); };

		nodeptr		make_node(const value_type& val)
		{
			nodptr	res = _alloc.allocate(node(), 1);
			_alloc.construct(res, node(val.first, val.second));
			return (res);
		};

		pair<iterator, bool>	insert_unique(const value_type& val)
		{
			iterator	res(find(val.first));

			if (*res != m_nullptr)
				return (ft::make_pair(res, false));
			else
				return (ft::make_pair(iterator(insert_node(make_node(val))), true));
		};
		iterator				insert_unique(const_iterator pos, const value_type& val)
		{
			iterator	res(find(val.first));

			if (*res != m_nullptr)
				return (ft::make_pair(res, false));
			else if (find(val.first, res._elem))
				return (ft::make_pair(iterator(insert_node(make_node(val)
												, res._elem)), true));
			else
				return (return (ft::make_pair(iterator(insert_node(make_node(val))), true));)
		};
		void					insert_multi(const_iterator first, const_iterator last);
		{
			while (first != last)
			{
				if (find(first._elem->_value->first) != m_nullptr)
					insert_node(make_node(first._elem->_value));
				++first;
			};
		};
		void	erase(const_iterator pos)
		{
			iterator	node = this->begin();
			while (node._elem != this->end())
			{
				if (node->_elem == pos->_elem)
				{
					delete_node(pos._elem);
					return ;
				}
			}
		};
		void	erase_unique(const key_type& key)
		{
			iterator	erase_pos(find(key));
			if (erase_pos._elem != m_nullptr)
				delete_node(erase_pos._elem);
		};
		void	erase_multi(const_iterator first, const_iterator last)
		{
			while (first == last)
				erase(first++);
		};
		iterator		find(const key_type& key, const nodeptr& start_node = _root)
		{
			while (start_node != m_nullptr)
			{
				if (value_compare.key_compare(start_node->_left->_value.first, key))
					start_node = start_node->_right;
				else if (value_compare.key_compare(key, start_node->_left->_value.first))
					start_node = start_node->_left;
				else
					return (start_node);
			}
			reture (m_nullptr);
		};
		const_iterator	find(const key_type& key, const nodeptr& start_node = _root) const
		{
			while (start_node != m_nullptr)
			{
				if (value_compare.key_compare(start_node->_left->_value.first, key))
					start_node = start_node->_right;
				else if (value_compare.key_compare(key, start_node->_left->_value.first))
					start_node = start_node->_left;
				else
					return (start_node);
			}
			reture (m_nullptr);
		};
		iterator		lower_bound(const key_type& key);
		const_iterator	lower_bound(const key_type& key) const;
		iterator		upper_bound(const key_type& key);
		const_iterator	upper_bound(const key_type& key) const;
	};

	template <class V, class Compare, class Alloc>
	void	tree<V, Compare, Alloc>::left_rotation(nodeptr x)
	{
		nodeptr	y = x->_right;
		x->_right = y->_left;
		if (y->_left != this->_nil)
			y->_left->parent = x;
		y->_left = x;
		y->_parent = x->_parent;
		if (x->_parent == this->_nil)
			this->_root = y;
		else if (x == x->_parent->_left)
			x->_parent->_left = y;
		else
			x->_parent->_right = y;
		x->_parent = y;
	};
	template <class V, class Compare, class Alloc>
	void	tree<V, Compare, Alloc>::right_rotation(nodeptr x)
	{
		nodeptr	x = y->_left;
		y->_left = x->_right;
		if (y->_right != this->_nil)
			y->_right->_parent = y;
		x->_right = y;
		x->_parent = y->_parent;
		if (y->_parent == this->_nil)
			this->_root = x;
		else if (y == y->_parent->_left)
			y->_parent->left = x;
		else
			y->_parent->_right = x;
		y->_parent = x;
	};

	template <class V, class Compare, class Alloc>
	nodeptr	tree<V, Compare, Alloc>::insert_node(nodeptr target_node, nodeptr criteria_node = _root)
	{
		this->_size += 1;
		nodeptr	parent_node = _nil;
		while (criteria_node != _nil)
		{
			parent_node = criteria_node;
			if (value_compare(target_node->_value, criteria_node->_value))
				criteria_node = criteria_node->_left;
			else
				criteria_node = criteria_node->_right;
		}
		target_node->_parent = parent_node;
		if (parent_node == _nil)
			_root = target_node;
		else if (value_compare(target_node->_value, parent_node->_value))
			parent_node->_left = target_node;
		else
			parent_node->_right = target_node;
		target_node->_left = _nil;
		target_node->_right = _nil;
		target_node->_color = Red;
		insert_fixup(target_node);
	};
	template <class V, class Compare, class Alloc>
	void	tree<V, Compare, Alloc>::insert_fixup(nodeptr target_node)
	{
		while (target_node->_parent->_color == Red)
		{
			nodeptr	uncle_node = find_bro_node(target_node->_parent);	// 삼촌 노드 생성
			if (target_node->_parent == uncle_node->_parent->_left)			// 삼촌 방향 확인
			{
				if (uncle_node->_color == Red)
				{
					target_node->_parent->_color = Black;			// 부모노드색 Black으로 변경
					uncle_node->_color = Black;						// 삼촌노드색 Black으로 변경
					target_node->_parent->_parent->_color = Red;	// 조부모노드색 Red로 변경
					target_node = target_node->_parent->_parent		// target을 조부모로 변경하여 재귀모델 생성
				}
				else	// 아래 과정은 색의 균형을 맞추기위해 회전시킨 것이다.
				{		// 부모 Red, 삼촌 Black으로 부모를 자식화시킨 것이다.
					if (target_node == target_node->_parent->_right)
					{												// target이 오른쪽노드인가?
						target_node == target_node->_parent;
						left_rotation(target_node);					// 좌회전
					}
					target_node->_parent->_color = Black;			// 부모노드색 Black으로 변경
					target_node->_parent->_parent->_color = Red;	// 조부모노드색 Red로 변경
					right_rotation(target_node);					// 우회전
				}
			}
			else
			{
				if (uncle_node->_color == Red)
				{
					target_node->_parent->_color = Black;			// 부모노드색 Black으로 변경
					uncle_node->_color = Black;						// 삼촌노드색 Black으로 변경
					target_node->_parent->_parent->_color = Red;	// 조부모노드색 Red로 변경
					target_node = target_node->_parent->_parent		// target을 조부모로 변경하여 재귀모델 생성
				}
				else	// 아래 과정은 색의 균형을 맞추기위해 회전시킨 것이다.
				{		// 부모 Red, 삼촌 Black으로 부모를 자식화시킨 것이다.
					if (target_node == target_node->_parent->_left)
					{												// target이 오른쪽노드인가?
						target_node == target_node->_parent;
						right_rotation(target_node);				// 우회전
					}
					target_node->_parent->_color = Black;			// 부모노드색 Black으로 변경
					target_node->_parent->_parent->_color = Red;	// 조부모노드색 Red로 변경
					left_rotation(target_node);						// 좌회전
				}
			}
		}
		_root->_color = Black;
	};
	template <class V, class Compare, class Alloc>
	void	tree<V, Compare, Alloc>::delete_node(nodeptr target_node)
	{
		this->_size -= 1;
		color_t	origin_color = target_node->_color;
		nodeptr	replace_node = find_replace_node(target_node);
		color_t	replace_node_color = replace_node->_color;
		if (replace_node != _nil)
		{
			nodeptr	fixup_node = replace_node->_right;
			replace(replace_node);
			replace_node->_color = origin_color;
			if (r_color == Black)
				delete_fixup(fixup_node);	// 검-검, 빨-검
		}
		else
			_root = _nil;
		remove_node(target_node);
	};
	template <class V, class Compare, class Alloc>
	void	tree<V, Compare, Alloc>::replace(nodeptr target_node, nodeptr replace_node)
	{
		replace_node->_parent = target_node->_parent;
		if (target_node->_left == replace_node)
		{
			replace_node->_left = _nil;
			replace_node->_right = target_node->_right;
			if (target_node->_right != _nil)
				target_node->_right->_parent = replace_node;
		}
		else if (target_node->_right == replace_node)
		{
			replace_node->_right = _nil;
			replace_node->_left = target_node->_left;
			if (target_node->_left != _nil)
				target_node->_left->_parent = replace_node;
		}
		else
		{
			replace_node->parent->_left = replace_node->_right;
			if (replace_node->_right != _nil)
				replace_node->_right->_parent = replace_node->_parent;
			if (target_node->_parent->_left == target_node)
				target_node->_parent->_left = replace_node;
			else
				target_node->_parent->_right = replace_node;
			replace_node->_left = target_node->_left;
			if (target_node->_left != _nil)
				target_node->_left->_parent = replace_node;
			replace_node->_right = target_node->_right;
			if (target_node->_right != _nil)
				target_node->_right->_parent = replace_node;
		}
	};
	template <class V, class Compare, class Alloc>
	void	tree<V, Compare, Alloc>::delete_fixup(nodeptr target_node)
	{
		while (target_node != _root && target_node->_color == Black)
		{
			nodeptr	bro_node = find_bro_node(target_node);
			if (target_node == target_node->_parent->_left)
			{
				if (bro_node->_color == Red)
				{
					bro_node->_color = Black;
					target_node->_parent->_color = Red;
					left_rotation(target_node->_parent);
					bro_node = target_node->_parent->_right;
				}
				if (bro_node->_left->_color == Black
					&& bro_node->_right->_color == Black)
				{
					bro_node->_color = Red;
					target_node = target_node->_parent;
				}
				else
				{
					if (bro_node->_right->_color == Black)
					{
						bro_node->_left->_color = Black;
						bro_node->_color = Red;
						right_rotation(bro_node);
						bro_node = target_node->_parent->_right;
					}
					bro_node->_color = target_node->_parent->_color;
					target_node->_parent->_color = Black;
					bro_node->_right->_color = Black;
					left_rotation(x->_parent);
					target_node = _root;
				}
			}
			else
			{
				if (bro_node->_color == Red)
				{
					bro_node->_color = Black;
					target_node->_parent->_color = Red;
					right_rotation(target_node->_parent);
					bro_node = target_node->_parent->_left;
				}
				if (bro_node->_left->_color == Black
					&& bro_node->_right->_color == Black)
				{
					bro_node->_color = Red;
					target_node = target_node->_parent;
				}
				else
				{
					if (bro_node->_left->_color == Black)
					{
						bro_node->_left->_color = Black;
						bro_node->_color = Red;
						left_rotation(bro_node);
						bro_node = target_node->_parent->_left;
					}
					bro_node->_color = target_node->_parent->_color;
					target_node->_parent->_color = Black;
					bro_node->_left->_color = Black;
					right_rotation(x->_parent);
					target_node = _root;
				}
			}
		}
		target_node->_color = Black;
	};
	template <class V, class Compare, class Alloc>
	void	tree<V, Compare, Alloc>::remove_node(nodeptr target_node)
	{
		_alloc.destroy(target_node);
		_alloc.deallocate(target_node, 1);
	};
	template <class V, class Compare, class Alloc>
	void	tree<V, Compare, Alloc>::all_clear(nodeptr node)
	{
		if (node != _nil)
			return ;
		else
		{
			all_clear(node->_left);
			all_clear(node->_right);
			remove_node(node);
		}
	};
};

#endif
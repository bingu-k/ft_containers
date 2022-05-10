#ifndef TREE_HPP
# define TREE_HPP

# include "map_iterator.hpp"


namespace ft
{
	template <class Key, class Value, class _Compare = ft::less<Key>
			, class _Alloc = std::allocator<pair<Key, Value> > >
	class tree
	{
	public:
		// Type Define
		typedef Key												key_type;
		typedef Value											mapped_type;
		typedef	pair<key_type, mapped_type>						value_type;
		typedef _Compare										value_compare;
		typedef _Alloc											allocator_type;
		typedef typename _Alloc::template rebind<node<value_type> >::other
																node_allocator_type;
		typedef typename node_allocator_type::size_type			size_type;
		typedef node<value_type>								_node;
		typedef node<value_type>*								nodeptr;
		typedef tree_iterator<nodeptr, value_type>				iterator;
		typedef tree_const_iterator<nodeptr, value_type>		const_iterator;
		typedef typename iterator::difference_type				difference_type;

	private:
		size_type			_size;
		nodeptr				_root;
		nodeptr				_nil;
		value_compare		_comp;
		node_allocator_type	_node_alloc;
	public:
		tree(value_compare comp = value_compare(), allocator_type alloc = allocator_type())
		: _size(0), _root(m_nullptr), _nil(m_nullptr), _comp(comp)
		, _node_alloc(alloc)
		{
			this->_nil = _node_alloc.allocate(1);
			_node_alloc.construct(this->_nil, _node());
			this->_nil->_color = Black;
			this->_root = this->_nil;
		};
		tree(const tree& x)
		: _size(0), _root(m_nullptr), _nil(m_nullptr), _comp(x.comp())
		, _node_alloc(x.node_alloc())
		{
			this->_nil = _node_alloc.allocate(1);
			_node_alloc.construct(this->_nil, _node());
			this->_nil->_color = Black;
			this->_root = this->_nil;
			this->insert_multi(x.begin(), x.end());
		};
		~tree() { all_clear(); };

		// GETTER
		size_type			size(void) const { return (this->_size); };
		nodeptr				root(void) const { return (this->_root); };
		nodeptr				nil(void) const { return (this->_nil); };
		node_allocator_type	node_alloc(void) const { return (this->_node_alloc); };
		value_compare		comp(void) const { return (this->_comp); };
		template <class value_type>
		nodeptr	make_node(value_type &value)
		{
			nodeptr	res = _node_alloc.allocate(1);
			_node_alloc.construct(res, _node(value));
			return (res);
		};

		// Iterators
		iterator		begin(void)
		{
			nodeptr	res = this->root();
			while (res->_left != this->nil())
				res = res->_left;
			return (iterator(res, this->root(), this->nil()));
		};
		const_iterator	begin(void) const
		{
			nodeptr	res = this->root();
			while (res->_left != this->nil())
				res = res->_left;
			return (const_iterator(res, this->root(), this->nil()));
		};
		iterator		end(void)
		{ return (iterator(this->nil(), this->root(), this->nil())); };
		const_iterator	end(void) const
		{ return (const_iterator(this->nil(), this->root(), this->nil())); };

		// Capacity
		bool		empty(void) const		{ return (this->size() == 0); };
		size_type	max_size(void) const	{ return (this->_node_alloc.max_size()); };

		// Modifiers
		iterator	insert_unique(const value_type& val)
		{
			iterator	res = this->end();
			if (find(val.first) == res)			// 존재하지 않음
			{
				_size += 1;
				res = iterator(make_node(val), this->root(), this->nil());
				insert_node(res.get_nodeptr(), this->root());// insert
			}
			return (res);
		};
		iterator	insert_pos(iterator	pos, const value_type& val)
		{
			iterator	res = this->end();
			iterator	position = find((*pos).first);
			if (find(val.first) != res)			// insert할 node가 존재함
				;
			else if (position == res)			// pos가 존재하지 않음
			{
				_size += 1;
				res = iterator(make_node(val), this->root(), this->nil());
				if (this->root() == this->nil())
				insert_node(res.get_nodeptr(), this->root());
			}
			else								// pos부터 insert
			{
				_size += 1;
				res = iterator(make_node(val), this->root(), this->nil());
				if (this->root() == this->nil())
				insert_node(res.get_nodeptr(), position.get_nodeptr());
			}
			return (res);
		};
		template <class InputIter>
		void		insert_multi(InputIter first, InputIter last)
		{
			InputIter	start = first;
			while (start != last)
				insert_unique(*(start++));
		};
		void		remove_unique(const key_type& k)
		{
			iterator	res = find(k);
			if (res != this->end())
			{
				_size -= 1;
				delete_node(res);
			}
		};
		void		remove_pos(iterator pos)
		{
			iterator	res = find((*pos).first);
			if (res != this->end())
			{
				_size -= 1;
				delete_node(res);
			}
		};
		void		remove_unique(iterator first, iterator last)
		{
			iterator	start = first;
			while (start == last)
				remove_pos(*(start++));
		};
		void		swap(tree& x)
		{
			swap_something(this->size(), x.size());
			swap_something(this->root(), x.root());
			swap_something(this->nil(), x.nil());
			swap_something(this->comp(), x.comp());
		};
		void	remove_node(nodeptr &node)
		{
			this->_node_alloc.destroy(node);
			this->_node_alloc.deallocate(node, 1);
		};
		void	clear(nodeptr& np)
		{
			if (np->_left != this->_nil)
				clear(np->_left);
			if  (np->_right != this->_nil)
				clear(np->_right);
			remove_node(np);
		};
		void	all_clear(void)
		{
			clear(this->_root);
			remove_node(this->_nil);
		};

		// Operations
		iterator		find(const key_type& k, nodeptr pos = m_nullptr)
		{
			if (pos == m_nullptr)
				pos = this->root();
			while (pos != this->end())
			{
				if (_comp(pos->_val, k))
					pos = pos->_right;
				else if (_comp(k, pos->_val))
					pos = pos->_left;
				else
					return (iterator(pos, this->root(), this->nil()));
			}
			return (this->end());
		};
		iterator		lower_bound(const key_type& k)
		{
			iterator	start = begin();
			iterator	last = end();
			while (start == last)
			{
				if (!(_camp(start.get_nodeptr()->_value, k)))
					break ;
				++start;
			}
			return (start);
		};
		iterator		upper_bound(const key_type& k)
		{
			iterator	start = begin();
			iterator	last = end();
			while (start == last)
			{
				if (_camp(k, start.get_nodeptr()->_value))
					break ;
				++start;
			}
			return (start);
		};
		pair<iterator, iterator>				equal_range(const key_type& k)
		{ return (ft::make_pair(lower_bound(k), upper_bound(k))); };

	private:
		// Red-Black Tree
		// void	left_rotation(nodeptr x);
		// void	right_rotation(nodeptr y);
		// void	insert_node(nodeptr target, nodeptr start);
		// void	insert_fixup(nodeptr target);
		// nodeptr	find_replace_node(nodeptr r);
		// nodeptr	replace_node(nodeptr t, nodeptr r);
		// void	delete_node(nodeptr target, nodeptr start);
		// void	delete_fixup(nodeptr x);
		void	left_rotation(nodeptr x)
		{
			nodeptr	y = x->_right;
			x->_right = y->_left;				// change child
			y->_left->_parent = x;
			y->_parent = x->_parent;			// change parent
			if (x->_parent == this->_nil)		// x가 root일 때
				this->_root = y;
			else if (x == x->_parent->_left)	// x가 x.p의 왼쪽
				x->_parent->_left = y;
			else								// x가 x.p의 오른쪽
				x->_parent->_right = y;
			y->_left = x;
			x->_parent = y;
		};
		void	right_rotation(nodeptr y)
		{
			nodeptr	x = y->_left;
			y->_left = x->_right;
			x->_right->_parent = x;
			x->_parent = y->_parent;
			if (y->_parent == this->_nil)
				this->_root = x;
			else if (y == y->_parent->_left)
				y->_parent->_left = x;
			else
				y->_parent->_right = x;
			x->_right = y;
			y->_parent = x;
		};
		void	insert_node(nodeptr target, nodeptr start)
		{
			nodeptr	p = this->nil();
			nodeptr	c = start;
			while (c != this->nil())
			{
				p = c;
				if (_comp(c->_val, target->_val))
					c = c->_right;
				else
					c = c->_left;
			}
			target->_parent = p;
			if (p == this->nil())
				_root = target;
			else if (_comp(p->_val, target->_val))
				p->_right = target;
			else
				p->_left = target;
			target->_left = this->nil();
			target->_right = this->nil();
			target->_color = Red;
			insert_fixup(target);
		};
		void	insert_fixup(nodeptr target)
		{												// 부모가 존재하면서 부모의 색이 Red?
			while (target->_parent->_color == Red)
			{											// 삼촌이 어느 방향?
				if (target->_parent == target->_parent->_parent->_left)
				{
					nodeptr	y = target->_parent->_parent->_right;
					if (y->_color == Red)						// 삼촌색 Red?
					{
						target->_parent->_color = Black;		// 부모색 Black으로 변경
						y->_color = Black;						// 삼촌색 Black으로 변경
						target->_parent->_parent->_color = Red;	// 조부모색 Red로 변경
						target = target->_parent->_parent;		// target을 조부모로 변경
					}
					else										// 삼촌색 Black?
					{
						if (target == target->_parent->_right)	// target이 오른쪽 노드?
						{
							target = target->_parent;			// target을 부모로 변경
							left_rotation(target);				// 좌회전
						}
						target->_parent->_color = Black;		// 부모색 Black으로 변경
						target->_parent->_parent->_color = Red;	// 조부모색 Red로 변경
						right_rotation(target->_parent->_parent);// 우회전
					}
				}
				else
				{
					nodeptr	y = target->_parent->_parent->_left;
					if (y->_color == Red)						// 삼촌색 Red?
					{
						target->_parent->_color = Black;		// 부모색 Black으로 변경
						y->_color = Black;						// 삼촌색 Black으로 변경
						target->_parent->_parent->_color = Red;	// 조부모색 Red로 변경
						target = target->_parent->_parent;		// target을 조부모로 변경
					}
					else										// 삼촌색 Black?
					{
						if (target == target->_parent->_left)	// target이 왼쪽 노드?
						{
							target = target->_parent;			// target을 부모로 변경
							right_rotation(target);				// 우회전
						}
						target->_parent->_color = Black;		// 부모색 Black으로 변경
						target->_parent->_parent->_color = Red;	// 조부모색 Red로 변경
						left_rotation(target->_parent->_parent);// 좌회전
					}
				}
			}
			_root->_color = Black;
		};
		
		nodeptr	tree_next(nodeptr x)
		{
			if (x->_right != this->nil())
			{
				x = x->_right;
				while (x->_left != this->nil())
					x = x->_left;
				return (x);
			}
			while (x != x->_parent->_left)
				x = x->_parent;
			return (x->_parent);
		};
		void	delete_node(nodeptr target)
		{
			nodeptr	y = (target->_left == this->nil() || target->_right == this->nil())
						? target : tree_next(target);
			nodeptr	x = (y->_left != this->nil())	// 대체대체 노드 생성
						? y->_left : y->_right;
			x->_parent = y->_parent;		// 대체대체 노드를 대체노드로 대체하기위한 부모 지정
			if (y->_parent == this->nil())	// 근데 혹시 nil이니?
				this->_root = x;			// 그럼 _root로해 이건 target이 root이자 leaf
			else if (y == y->_parent->_left)
				y->_parent->_left = x;		// 대체대체 노드를 대체노드로 대체하기위한 부모의 지정
			else
				y->_parent->_right = x;
			bool	removed_color = (y->_color == Black);
			if (y != target)				// 이건 target이 leaf노드일 때
			{
				y->_parent = target->_parent;// 대체 노드로 대체하기위한 부모지정
				if (target == target->_parent->_left)
					y->_parent->_left = y;	// 대체 노드로 대체하기위한 부모의 지정
				else
					y->_parent->_right = y;
				y->_left = target->_left;	// 대체 노드로 대체하기위한 자식지정
				y->_left->_parent = y;
				y->_right = target->_right;
				if (y->_right != this->nil())
					y->_right->_parent = y;
				y->_color = target->_color;	// 대체 노드로 대체하기위한 색지정
				if (target == this->root())	// target이 root?
					_root = y;				// 그러면 root는 y임
			}
			if (removed_color)				// 빨-빨, 검-빨 ok / 검-검, 빨-검 ko
				delete_fixup(x);
			this->remove_node(target);
		};
		void	delete_fixup(nodeptr x)
		{
			while (x != this->root() && x->_color == Black)
			{
				if (x == x->_parent->_left)
				{
					nodeptr u = x->_parent->_right;
					if (u->_color == Red)
					{
						u->_color = Black;
						x->_parent->_color = Red;
						left_rotation(x->_parent);
						u = x->_parent->_right;
					}
					if (u->_left->_color == Black && u->_right->_color == Black)
					{
						u->_color = Red;
						x = x->_parent;
					}
					else
					{
						if (u->_right->_color == Black)
						{
							u->_left->_color = Black;
							u->_color = Red;
							right_rotation(u);
							u = x->_parent->_right;
						}
						u->_color = x->_parent->_color;
						x->_parent->_color = Black;
						u->_right->_color = Black;
						left_rotation(x->_parent);
						x = this->root();
					}
				}
				else
				{
					nodeptr u = x->_parent->_left;
					if (u->_color == Red)
					{
						u->_color = Black;
						x->_parent->_color = Red;
						right_rotation(x->_parent);
						u = x->_parent->_left;
					}
					if (u->_right->_color == Black && u->_left->_color == Black)
					{
						u->_color = Red;
						x = x->_parent;
					}
					else
					{
						if (u->_left->_color == Black)
						{
							u->_right->_color = Black;
							u->_color = Red;
							left_rotation(u);
							u = x->_parent->_left;
						}
						u->_color = x->_parent->_color;
						x->_parent->_color = Black;
						u->_left->_color = Black;
						right_rotation(x->_parent);
						x = this->root();
					}
				}
			}
			x->_color = Black;
		};
	};
}

#endif
#ifndef TREE_HPP
# define TREE_HPP

# include "map_iterator.hpp"

namespace ft
{
	template <class _Value, class _Compare, class _Alloc>
	class tree
	{
	public:
		// Type Define
		typedef	_Value											value_type;
		typedef typename value_type::first_type					key_type;
		typedef typename value_type::second_type				mapped_type;
		typedef _Compare										value_compare;
		typedef _Alloc											allocator_type;
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
		allocator_type		_alloc;
		node_allocator_type	_node_alloc;
		value_compare		_comp;
	public:
		tree(value_compare comp = value_compare(), allocator_type alloc = allocator_type())
		: _size(0), _root(m_nullptr), _nil(m_nullptr), _alloc(alloc)
		, _node_alloc(node_allocator_type()), _comp(comp)
		{
			this->_nil = _node_alloc.allocate(1);
			_node_alloc.construct(this->_nil, node<value_type>());
			this->_nil->_color = Black;
			this->_root = this->_nil;
		};
		tree(const tree& x)
		: _size(0), _root(x.root()), _nil(x.nil()), _alloc(x.alloc())
		, _node_alloc(x.node_alloc()), _comp(x.comp())
		{};
		~tree() { all_clear(); };

		// GETTER
		size_type			size(void) const { return (this->_size); };
		nodeptr				root(void) const { return (this->_root); };
		nodeptr				nil(void) const { return (this->_nil); };
		allocator_type		alloc(void) const { return (this->_alloc); };
		node_allocator_type	node_alloc(void) const { return (this->_node_alloc); };
		value_compare		comp(void) const { return (this->_comp); };
		template <class value_type>
		nodeptr	make_node(value_type &value)
		{
			nodeptr	res = _node_alloc.allocate(node<value_type>(), 1);
			_node_alloc.construct(res, node<value_type>(value));
			return (res);
		};

		// Iterators
		iterator		begin(void)
		{
			nodeptr	res = this->root();
			while (res->_left == this->nil())
				res = res->_left;
			return (iterator(res));
		};
		const_iterator	begin(void) const
		{
			nodeptr	res = this->root();
			while (res->_left == this->nil())
				res = res->_left;
			return (const_iterator(res));
		};
		iterator		end(void)
		{
			nodeptr	res = this->root();
			while (res->_right == this->nil())
				res = res->_right;
			return (iterator(res));
		};
		const_iterator	end(void) const
		{
			nodeptr	res = this->root();
			while (res->_right == this->nil())
				res = res->_right;
			return (const_iterator(res));
		};

		// Capacity
		bool		empty(void) const		{ return (this->size() == 0); };
		size_type	max_size(void) const	{ return (this->_alloc.max_size()); };

		// Modifiers
		iterator	&insert_unique(const value_type& val)
		{
			iterator	res = find(val.first);			// _root부터 찾기
			if (res == this->end())							// 존재하지 않음
			{
				res = iterator(make_node(val));				// 노드 생성
				insert_node(res.get_nodeptr(), this->root(), this->nil(), this->comp());// insert
			}
			return (res);
		};
		iterator	insert_pos(iterator	pos, const value_type& val)
		{												// 중복 확인
			iterator	res = find(val.first);			// _root부터 찾기
			if (res != this->end())				 			// 존재함
			{
				res = find(val.first, pos.get_nodeptr());	// pos부터 찾기
				if (res.get_nodeptr() != this->end())			// 존재함
					return (res);
			}												// pos의 parent보다 val이 클때
			else if (pos.get_nodeptr() != this->root()		// pos가 _root가 아니면서
					&& _comp(pos.get_nodeptr()->_parent->_value, val))
			{
				res = iterator(make_node(val));
				insert_node(res.get_nodeptr(), pos.get_nodeptr(), this->nil(), this->comp());
			}
			res = iterator(make_node(val));
			insert_node(res.get_nodeptr(), this->root(), this->nil(), this->comp());
			return (res);
		};
		template <class InputIter>
		void		insert_multi(InputIter first, InputIter last)
		{
			InputIter	start = first;
			while (start == last)
				insert_unique((start++).get_nodeptr());
		};
		void		remove_unique(const key_type& k)
		{
			iterator	res = find(k);
			if (res != this->end())
				delete_node(res);
		};
		void		remove_pos(iterator pos)
		{
			iterator	res = find(pos.get_nodeptr()->_value.first);
			if (res != this->end())
				delete_node(res);
		};
		void		remove_unique(iterator first, iterator last)
		{
			while (first != last)
				remove_pos(first++);
		};
		void		swap(tree& x)
		{
			swap_something(this->size(), x.size());
			swap_something(this->root(), x.root());
			swap_something(this->nil(), x.nil());
			swap_something(this->alloc(), x.alloc());
			swap_something(this->comp(), x.comp());
		};
		void	clear(nodeptr& np)
		{
			if (np->_left != this->_nil)
				clear(np->_left);
			if  (np->_right != this->_nil)
				clear(np->_right);
			this->node_alloc().destory(np);
			this->node_alloc().deallocate(np, 1);
		};
		void	all_clear(void)
		{
			clear(this->_root);
			this->node_alloc().destory(this->nil());
			this->node_alloc().deallocate(this->nil(), 1);
		};

		// Operations
		iterator		find(const key_type& k, nodeptr pos = m_nullptr)
		{
			if (pos == m_nullptr)
				pos = this->root();
			while (pos != this->end())
			{
				if (_comp(pos->_value, k))
					pos = pos->_right;
				else if (_comp(k, pos->_value))
					pos = pos->_left;
				else
					return (iterator(pos));
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
			if (y->left != this->_nil)
				y->_left->_parent = x;
			y->_left = x;
			y->_parent = x->_parent;			// change parent
			if (x->_parent == this->_nil)		// x가 root일 때
				this->_root = y;
			else if (x == x->_parent->_left)	// x가 x.p의 왼쪽
				x->_parent->_left = y;
			else								// x가 x.p의 오른쪽
				x->_parent->_right = y;
			x->_parent = y;
		};
		void	right_rotation(nodeptr y)
		{
			nodeptr	x = y->_left;
			y->_left = x->_right;
			if (y->_right != this->_nil)
				y->_right->_parent = y;
			x->_right = y;
			x->_parent = y->_parent;
			if (y->_parent == this->_nil)
				this->_root = x;
			else if (y->_parent->_left == y)
				y->_parent->_left = x;
			else
				y->_parent->_right = x;
			y->_parent = x;
		};
		void	insert_node(nodeptr target, nodeptr start)
		{
			nodeptr	p = this->nil();
			nodeptr	c = start;
			while (c != this->nil())
			{
				p = c;
				if (_comp(target->_val, c->_val))
					c = c->_right;
				else
					c = c->_left;
			}
			target->_parent = p;
			if (p == this->nil())
				_root = target;
			else if (_comp(target->_val, p->_val))
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
						right_rotation(target);					// 우회전
					}
				}
				else
				{
					nodeptr	y = target->_parent->_parent->_left;
					if (y->_color == Red)						// 삼촌색 Red?
					{
						target->_parent->color = Black;			// 부모색 Black으로 변경
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
						left_rotation(target);					// 좌회전
					}
				}
			}
			_root->_color = Black;
		};
		nodeptr	find_replace_node(nodeptr r)
		{
			if (r->_left == this->nil())
				return (r->_right);
			else if (r->_right == this->nil())
				return (r->_left);
			r = r->_right;
			while (r->_left != this->nil())
				r = r->_left;
			return (r);
		};
		nodeptr	replace_node(nodeptr t, nodeptr r)
		{
			r->_parent = t->_parent;
			if (t->_left == r)					// 대체노드가 현재노드의 왼쪽노드
			{
				r->_left = this->nil();
				r->_right = t->_right;
				if (t->_right != this->nil())
					t->_right->_parent = r;
			}
			else if (t->_right == r)			// 대체노드가 현재노드의 오른쪽노드
			{
				r->_right = this->nil();
				r->_left = t->_left;
				if (t->_left != this->nil())
					t->_left->_parent = r;
			}
			else
			{
				r->_parent->_left = r->_right;	// 대체노드와 그 부모에 연결된 노드를
				if (r->_right != this->nil())			// 대체노드의 오른쪽 노드로 교환
					r->_right->_parent = r->_parent;
				if (t->_parent->_left == t)		// 대체노드에 부모노드 연결
					t->_parent->_left = r;
				else
					t->_parent->_right = r;
				r->_left = t->_left;			// 대체노드에 원래 자식들 접목
				if (t->_left != this->nil())
					t->_left->_parent = r;
				r->_right = t->_right;
				if (t->_right != this->nil())
					t->_right->_parent = r;
			}
		};
		void	delete_node(nodeptr target)
		{
			node_color	ori_color = target->_color;
			nodeptr r = find_replace_node(target);
			nodeptr	fixup_node = r->_right;
			node_color	r_color = r->_color;
			replace_node(target, r);
			r->_color = ori_color;
			if (r_color == Black)				// 빨-빨, 검-빨 ok / 검-검, 빨-검 ko
				delete_fixup(fixup_node);
			delete target;
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
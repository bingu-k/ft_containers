#ifndef TREE_HPP
# define TREE_HPP

# include "map_iterator.hpp"
# include <iostream>

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
		nodeptr				_end;
		value_compare		_comp;
		allocator_type		_alloc;
		node_allocator_type	_node_alloc;
	public:
		tree(value_compare comp = value_compare(), allocator_type alloc = allocator_type())
		: _size(0), _root(m_nullptr), _end(m_nullptr), _comp(comp), _alloc(alloc)
		, _node_alloc(node_allocator_type())
		{
			this->_end = make_nil_node();
			this->_root = this->_end;
		};
		tree(const tree& x)
		: _size(0), _root(m_nullptr), _end(m_nullptr), _comp(x.comp()), _alloc(allocator_type())
		, _node_alloc(x.node_alloc())
		{
			this->_end = make_nil_node();
			this->_root = make_nil_node();
			this->insert_multi(x.begin(), x.end());
		};
		tree&	operator=(const tree& origin)
		{
			if (this != &origin)
			{
				this->all_clear();
				this->_comp = origin.comp();
				this->_node_alloc = origin.node_alloc();
				this->_end = make_nil_node();
				this->_root = this->_end;
				this->insert_multi(origin.begin(), origin.end());
			}
			return (*this);
		};
		~tree()
		{
			all_clear();
			remove_node(this->_end);
		};

		// GETTER
		size_type			size(void) const { return (this->_size); };
		nodeptr				root(void) const { return (this->_root); };
		value_compare		comp(void) const { return (this->_comp); };
		node_allocator_type	node_alloc(void) const { return (this->_node_alloc); };
		nodeptr	make_nil_node(void)
		{
			nodeptr	temp = _node_alloc.allocate(1);
			_node_alloc.construct(temp, _node());
			temp->_parent = m_nullptr;
			temp->_left = m_nullptr;
			temp->_right = m_nullptr;
			temp->_color = Black;
			return (temp);
		}
		template <class value_type>
		nodeptr	make_node(value_type &value)
		{
			nodeptr	res = _node_alloc.allocate(1);
			_node_alloc.construct(res, _node(value));		// 본인 초기화
			res->_parent = m_nullptr;
			res->_left = make_nil_node();
			res->_left->_parent = res;
			res->_right = make_nil_node();
			res->_right->_parent = res;
			return (res);
		};

		// Iterators
		iterator		begin(void)
		{
			nodeptr	res = this->root();
			if (res != m_nullptr && !is_nil(res))
			{
				while (!is_nil(res->_left))
					res = res->_left;
			}
			return (iterator(res, this->_end));
		};
		const_iterator	begin(void) const
		{
			nodeptr	res = this->root();
			if (res != m_nullptr && !is_nil(res))
			{
				while (!is_nil(res->_left))
					res = res->_left;
			}
			return (const_iterator(res, this->_end));
		};
		iterator		end(void)
		{ return (iterator(this->_end, this->_end)); };
		const_iterator	end(void) const
		{ return (const_iterator(this->_end, this->_end)); };

		// Capacity
		bool		empty(void) const		{ return (this->size() == 0); };
		size_type	max_size(void) const	{ return (this->_node_alloc.max_size()); };

		// Modifiers
		pair<iterator, bool>	insert_unique(const value_type& val)
		{
			iterator	res = find(val.first);
			if (res == end())			// 존재하지 않음
			{
				_size += 1;
				res = iterator(insert_node(make_node(val), this->root()), this->root());
				return (ft::pair<iterator,bool>(res, true));
			}
			return (ft::pair<iterator,bool>(res, false));
		};
		iterator	insert_pos(iterator	pos, const value_type& val)
		{
			iterator	res = find(val.first);
			if (res == end())			// 중복 아님
			{							// pos의 자식 노드 위치 확인
				_size += 1;
				res = iterator(make_node(val), this->_end);
				nodeptr	temp_node = this->root();
				while (!is_nil(temp_node))
				{
					if (_comp(val, temp_node->_val))
						temp_node = temp_node->_left;
					else
						temp_node = temp_node->_right;
				}
				if (pos.get_nodeptr() != m_nullptr && !is_nil(pos.get_nodeptr())
				&& (temp_node == pos.get_nodeptr()->_left || temp_node == pos.get_nodeptr()->_right))
					insert_node(res.get_nodeptr(), pos.get_nodeptr());
				else
					insert_node(res.get_nodeptr(), this->root());
			}
			return (res);
		};
		template <class InputIter>
		void		insert_multi(InputIter first, InputIter last)
		{
			InputIter	start = first;
			while (start != last)
			{
				insert_unique(*start);
				++start;
			}
		};
		size_type		remove_unique(const key_type& k)
		{
			iterator	res = find(k);
			if (res != this->end())
			{
				_size -= 1;
				nodeptr	deleted_node = res.get_nodeptr();
				delete_node(deleted_node);
				remove_node(deleted_node);
				return (1);
			}
			return (0);
		};
		void		remove_pos(iterator pos)
		{
			iterator	res = find((*pos).first);
			if (res != this->end())
			{
				_size -= 1;
				nodeptr	deleted_node = res.get_nodeptr();
				delete_node(deleted_node);
				remove_node(deleted_node);
			}
		};
		void		remove_multi(iterator first, iterator last)
		{
			iterator	start = first;
			nodeptr		deleted_node = m_nullptr;
			while (start != last)
			{
				_size -= 1;
				deleted_node = start.get_nodeptr();
				++start;
				delete_node(deleted_node);
				remove_node(deleted_node);
			}
		};
		void		swap(tree& x)
		{
			swap_something(this->_size, x._size);
			swap_something(this->_root, x._root);
			swap_something(this->_end, x._end);
			swap_something(this->_comp, x._comp);
			swap_something(this->_alloc, x._alloc);
			swap_something(this->_node_alloc, x._node_alloc);
		};
		void	remove_node(nodeptr& node)
		{
			this->_node_alloc.destroy(node);
			this->_node_alloc.deallocate(node, 1);
			node = m_nullptr;
		};
		void	clear(nodeptr &np)
		{
			if (np != this->_end)
			{
				if (!is_nil(np))
				{
					clear(np->_left);
					clear(np->_right);
				}
				remove_node(np);
			}
		};
		void	all_clear(void)
		{
			this->_size = 0;
			if (this->_root != m_nullptr)
				clear(this->_root);
			this->_end->_parent = m_nullptr;
			this->_root = this->_end;
		};

		// Operations
		iterator		find(const key_type& k, nodeptr pos = m_nullptr)
		{
			if (pos == m_nullptr)
				pos = this->root();
			while (!is_nil(pos))
			{
				if (_comp(pos->_val, k))
					pos = pos->_right;
				else if (_comp(k, pos->_val))
					pos = pos->_left;
				else
					return (iterator(pos, this->_end));
			}
			return (this->end());
		};
		const_iterator		find(const key_type& k, nodeptr pos = m_nullptr) const
		{
			if (pos == m_nullptr)
				pos = this->root();
			while (!is_nil(pos))
			{
				if (_comp(pos->_val, k))
					pos = pos->_right;
				else if (_comp(k, pos->_val))
					pos = pos->_left;
				else
					return (iterator(pos, this->_end));
			}
			return (this->end());
		};
		size_type	count(const key_type& k) const
		{
			if (find(k) == this->end())
				return (0);
			else
				return (1);
		};
		iterator		__lower_bound(const key_type& k, nodeptr rt, nodeptr res)
		{
			while (!is_nil(rt))
			{
				if (!_comp(rt->_val, k))
				{
					res = rt;
					rt = rt->_left;
				}
				else
					rt = rt->_right;
			}
			return (iterator(res, this->_end));
		};
		const_iterator	__lower_bound(const key_type& k, nodeptr rt, nodeptr res) const
		{
			while (!is_nil(rt))
			{
				if (!_comp(rt->_val, k))
				{
					res = rt;
					rt = rt->_left;
				}
				else
					rt = rt->_right;
			}
			return (const_iterator(res, this->_end));
		};
		iterator		lower_bound(const key_type& k)
		{ return (__lower_bound(k, this->root(), this->end().get_nodeptr())); };
		const_iterator	lower_bound(const key_type& k) const
		{ return (__lower_bound(k, this->root(), this->end().get_nodeptr())); };
		iterator		__upper_bound(const key_type& k, nodeptr rt, nodeptr res)
		{
			while (!is_nil(rt))
			{
				if (_comp(k, rt->_val))	//주어진 키 < 기준 키
				{
					res = rt;
					rt = rt->_left;
				}
				else					// 주어진 키 >= 기준 키
					rt = rt->_right;
			}
			return (iterator(res, this->_end));
		};
		const_iterator	__upper_bound(const key_type& k, nodeptr rt, nodeptr res) const
		{
			while (!is_nil(rt))
			{
				if (_comp(k, rt->_val))
				{
					res = rt;
					rt = rt->_left;
				}
				else
					rt = rt->_right;
			}
			return (const_iterator(res, this->_end));
		};
		iterator		upper_bound(const key_type& k)
		{ return (__upper_bound(k, this->root(), this->end().get_nodeptr())); };
		const_iterator		upper_bound(const key_type& k) const
		{ return (__upper_bound(k, this->root(), this->end().get_nodeptr())); };
		pair<iterator, iterator>	equal_range(const key_type& k)
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
			if (x == this->root())				// x가 root일 때
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
			x->_right->_parent = y;
			x->_parent = y->_parent;
			if (y == this->root())
				this->_root = x;
			else if (y == y->_parent->_left)
				y->_parent->_left = x;
			else
				y->_parent->_right = x;
			x->_right = y;
			y->_parent = x;
		};
		nodeptr	insert_node(nodeptr target, nodeptr start)
		{
			nodeptr	x = start;
			nodeptr	y = x->_parent;
			while (!is_nil(x))
			{
				y = x;
				if (_comp(target->_val, x->_val))
					x = x->_left;
				else
					x = x->_right;
			}
			target->_parent = y;
			if (y == m_nullptr)
			{
				remove_node(target->_right);
				target->_right = this->_end;
				target->_right->_parent = target;
				this->_root = target;
				target->_color = Black;
				return (this->_root);
			}
			else if (_comp(target->_val, y->_val))
			{
				remove_node(y->_left);
				y->_left = target;
			}
			else
			{
				remove_node(target->_right);
				target->_right = y->_right;
				target->_right->_parent = target;
				y->_right = target;
			}
			target->_color = Red;
			insert_fixup(target);
			return (target);
		};

		void	insert_fixup(nodeptr target)
		{												// 부모가 존재하면서 부모의 색이 Red?
			while (target != this->root() && target->_parent->_color == Red)
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
					if (y->_color == Red)
					{
						target->_parent->_color = Black;
						y->_color = Black;
						target->_parent->_parent->_color = Red;
						target = target->_parent->_parent;
					}
					else
					{
						if (target == target->_parent->_left)
						{
							target = target->_parent;
							right_rotation(target);
						}
						target->_parent->_color = Black;
						target->_parent->_parent->_color = Red;
						left_rotation(target->_parent->_parent);
					}
				}
			}
			_root->_color = Black;
		};
		
		nodeptr	tree_next(nodeptr x)
		{
			if (!is_nil(x->_right))
			{
				x = x->_right;
				while (!is_nil(x->_left))
					x = x->_left;
			}
			else
			{
				while (x == x->_parent->_right)
					x = x->_parent;
				x = x->_parent;
			}
			return (x);
		};
		void	delete_node(nodeptr target)
		{
			nodeptr	y = (is_nil(target->_left) || is_nil(target->_right))
						? target : tree_next(target);
			nodeptr	x = (!is_nil(y->_left)) ? y->_left : y->_right;
										// 대체대체 노드 생성
			x->_parent = y->_parent;
			if (y->_parent == m_nullptr)	// 근데 혹시 nil이니?
				this->_root = x;			// 그럼 _root로해 이건 target이 root이자 leaf
			else if (y == y->_parent->_left)
				y->_parent->_left = x;		// 대체대체 노드를 대체노드로 대체하기위한 부모의 지정
			else
				y->_parent->_right = x;
			bool	removed_color = (y->_color == Black);
			if (y != target)
			{
				y->_parent = target->_parent;// 대체 노드로 대체하기위한 부모지정
				if (target == this->root())	// target이 root?
					_root = y;				// 그러면 root는 y임
				else if (target == target->_parent->_left)
					target->_parent->_left = y;	// 대체 노드로 대체하기위한 부모의 지정
				else
					target->_parent->_right = y;
				remove_node(y->_left);
				target->_left->_parent = y;
				y->_left = target->_left;	// 대체 노드로 대체하기위한 자식지정
				target->_right->_parent = y;
				y->_right = target->_right;
				y->_color = target->_color;	// 대체 노드로 대체하기위한 색지정
			}
			else
			{
				if (y->_left == x)
					remove_node(y->_right);
				else
					remove_node(y->_left);
			}
			if (removed_color)			// 빨-빨, 검-빨 ok / 검-검, 빨-검 ko
				delete_fixup(x);
			nodeptr	node = this->root();
			if (!is_nil(node))
			{
				while (!is_nil(node->_right))
					node = node->_right;
				node->_right = this->_end;
			}
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
					if (u->_left->_color == Black && u->_right->_color == Black)
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
	public:
		void	inorder(nodeptr	node)
		{
			if (node == m_nullptr)
				return ;
			else
			{
				inorder(node->_left);
				if (node->_color == Black)
					std::cout << "Black ";
				else
					std::cout << "Red ";
				std::cout << "node\tkey : " << node->_val.first << "\tvalue : " << node->_val.second << std::endl;
				inorder(node->_right);
			}
		};
		void	preorder(nodeptr node)
		{
			if (node == m_nullptr)
				return ;
			else
			{
				if (node->_color == Black)
					std::cout << "Black ";
				else
					std::cout << "Red ";
				std::cout << "node\tkey : " << node->_val.first << "\tvalue : " << node->_val.second << std::endl;
				preorder(node->_left);
				preorder(node->_right);
			}
		};
	};
}

#endif
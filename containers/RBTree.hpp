#ifndef RBTREE_HPP
# define RBTREE_HPP

# include <memory>
# include <iostream>
# include "pair.hpp"
# include "iterator.hpp"
# include "node.hpp"

namespace ft
{
	template <class T, class Comp, class Alloc>
	class tree_base
	{
	public:
		typedef T			node_type;
		typedef size_t		size_type;
		typedef T*			pointer;
		typedef T const*	const_pointer;
		typedef T&			reference;
		typedef T const &	const_reference;
		typedef node<T>*	nodeptr;
	protected:
		nodeptr	_root;
		nodeptr	_nil;
	public:
		tree_base(void) : _root(m_nullptr), _nil(m_nullptr)
		{
			this->_nil = new node();
			this->_nil->_color = Black;
			this->_root = this->_nil;
		};
		tree_base(const tree_base& origin)
		{
			this->_root = new node(origin._root);
			this->_nil = new node();
			this->_nil->_color = Black;
			this->_root->_parent = this->_nil;
		};
		tree_base	&operator=(const tree_base& origin)
		{
			if (this != &origin)
			{
				if (this->_root)
					all_clear(this->_root);
				this->_root = new node(origin._root);
				this->_root->_parent = this->_nil;
			}
			return (*this);
		};
		virtual ~tree_base(void)
		{
			all_clear(this->_root);
			delete this->_nil;
		};

		// Rotation
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
				y->_parent->left = x;
			else
				y->_parent->_right = x;
			y->_parent = x;
		};

		// Insert
		void	insert(nodeptr target)
		{
			nodeptr	p = _nil;
			nodeptr	c = _root;
			while (c != _nil)
			{
				p = c;
				if (Comp(target->_val, c->_val))
					c = c->_right;
				else
					c = c->_left;
			}
			target->_parent = p;
			if (p == _nil)
				_root = target;
			else if (Comp(target->_val, p->_val))
				p->_right = target;
			else
				p->_left = target;
			target->_left = _nil;
			target->_right = _nil;
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

		// Find Node
		nodeptr	find_node(node_type n)
		{};

		// Delete
		nodeptr	find_replace_node(nodeptr r)
		{
			if (r->_left == _nil)
				return (r->_right);
			else if (r->_right == _nil)
				return (r->_left);
			r = r->_right;
			while (r->_left != _nil)
				r = r->_left;
			return (r);
		};
		nodeptr	replace_node(nodeptr t, nodeptr r)
		{
			r->_parent = t->_parent;
			if (t->_left == r)					// 대체노드가 현재노드의 왼쪽노드
			{
				r->_left = _nil;
				r->_right = t->_right;
				if (t->_right != _nil)
					t->_right->_parent = r;
			}
			else if (t->_right == r)			// 대체노드가 현재노드의 오른쪽노드
			{
				r->_right = _nil;
				r->_left = t->_left;
				if (t->_left != _nil)
					t->_left->_parent = r;
			}
			else
			{
				r->_parent->_left = r->_right;	// 대체노드와 그 부모에 연결된 노드를
				if (r->_right != _nil)			// 대체노드의 오른쪽 노드로 교환
					r->_right->_parent = r->_parent;
				if (t->_parent->_left == t)		// 대체노드에 부모노드 연결
					t->_parent->_left = r;
				else
					t->_parent->_right = r;
				r->_left = t->_left;			// 대체노드에 원래 자식들 접목
				if (t->_left != _nil)
					t->_left->_parent = r;
				r->_right = t->_right;
				if (t->_right != _nil)
					t->_right->_parent = r;
			}
		};
		void	delete(nodeptr target)
		{
			color_t	ori_color = target->_color;
			nodeptr r = find_replace_node(target);
			nodeptr	fixup_node = r->_right;
			color_t	r_color = r->_color;
			replace_node(r);
			r->_color = ori_color;
			if (r_color == Black)				// 빨-빨, 검-빨 ok / 검-검, 빨-검 ko
				delete_fixup(fixup_node);
			delete target;
		};
		void	delete_fixup(nodeptr x)
		{
			while (x != _root && x->_color == Black)
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
						x = _root;
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
						x = _root;
					}
				}
			}
			x->_color = Black;
		};
	};

	template <class T>
	class tree_iterator
	{
	public:
		typedef T											iterator_type;
		typedef iterator<bidirectional_iterator_tag(), T>	iter;
		typedef 
	};
};

#endif
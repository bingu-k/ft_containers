#ifndef RBTREE_HPP
# define RBTREE_HPP

# include <memory>
# include <iostream>
# include "utils.hpp"
# include "pair.hpp"

namespace ft
{
	typedef enum
	{
		Red,
		Black
	} color_t;

	template <class T, class Comp>
	class tree_base
	{
	public:
		typedef T			node_type;
		typedef size_t		size_type;
		typedef T*			pointer;
		typedef T const *	const_pointer;
		typedef T&			reference;
		typedef T const &	const_reference;
		struct node
		{

			node_type	_val = m_nullptr;
			color_t		_color = Red;
			node*		_parent = m_nullptr;
			node*		_left = m_nullptr;
			node*		_right = m_nullptr;
			node(node_type val = m_nullptr)
			: _val(_val), _color(Red), _parent(m_nullptr), _left(m_nullptr), _right(m_nullptr)
			{}
			node(const node& origin)
			: _val(origin._val), _color(origin._color), _parent(origin._parent), _left(origin._left), _right(origin._right)
			{}
		};
		typedef node*		nodeptr;
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
			if (y->_left != this->_nil)
				y->_left->_parent = y;
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
		void	insert_fixup_left_node(nodeptr target, nodeptr y)
		{
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
		};
		void	insert_fixup_right_node(nodeptr target, nodeptr y)
		{
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
		};
		void	insert_fixup(nodeptr target)
		{												// 부모가 존재하면서 부모의 색이 Red?
			while (target->_parent->_color == Red)
			{											// 삼촌이 어느 방향?
				if (target->_parent == target->_parent->_parent->_left)
					insert_fixup_left_node(target, target->_parent->_parent->_right);
				else
					insert_fixup_right_node(target, target->_parent->_parent->_left);
			}
			_root->_color = Black;
		};

		// Delete
		nodeptr	sibling(nodeptr target)
		{
			if (target->_left == _nil)
				return (target->_parent->_right);
			else
				return (target->_parent->_left);
		};
		void	replace_node(nodeptr target, nodeptr child)
		{
			child->_parent = target->_parent;
			if (target->_parent->_left == target)
				target->_parent->_left = child;
			else
				target->_parent->_right = child;
		};
		void	delete(nodeptr target)
		{
			replace_node(target, child);		// target과 child의 위치를 변경한다.
			if (target->_color == Black)		// target색이 Black?
			{
				if (child->_color == Red)		// child색이 Red?
					child->_color = Black;		// child색 Black으로 변경
				else
					delete_case1(target);		// delete case로 입장.
			}
			delete target;						// target을 free한다.
		};
		void	delete_case1(nodeptr target)
		{
			if (target->_parent != this->_nil)	// target이 루트노드가 아닌가?
				delete_case2(target);
		};
		void	delete_case2(nodeptr target)
		{
			nodeptr	y = sibling(target);
			if (y->_color == Red)						// 형제노드의 색이 Red
			{
				target->_parent->_color = Red;			// 부모노드의 색을 Red로 변경
				y->_color = Black;						// 형제노드의 색을 Black으로 변경
				if (target == target->_parent->_left)	// 해당노드가 왼쪽노드?
					left_rotation(target->_parent);		// 부모노드를 좌회전
				else									// 해당노드가 오른쪽노드?
					right_rotation(target->_parent);	// 부모노드를 우회전
			}
			delete_case3(target);
		};
		void	delete_case3(nodeptr target)
		{
			nodeptr	y = sibling(target);				// 부모노드의 색이 Black, 형제노드의 색이 Black, 형제노드의 자식노드들의 색이 Black
			if (target->_parent->_color == Black && y->_color == Black
					&& y->_left->_color == Black && y->_right->_color == Black)
			{
				y->_color = Red;						// 형제노드의 색을 Red로 변경
				delete_case1(target);					// 1case로 리턴
			}
			else
				delete_case4(target);
		};
		void	delete_case4(nodeptr target)
		{
			nodeptr	y = sibling(target);
			if (target->_parent->_color == Red && y->_color == Black
				&& y->_left->_color == Black && y->_right->_color == Black)
			{
				y->_color = Red;
				target->_parent->_color = Black;
			}
			else
				delete_case5(target);
		};
		void	delete_case5(nodeptr target)
		{
			nodeptr	y = sibling(target);
			if (y->_color == Black)
			{
				if (target == target->_parent->_left && y->_right->_color == Black
					&& y->_left->_color == Red)
				{
					y->_color = Red;
					y->_left->_color = Black;
					right_rotation(y);
				}
				else if (target == target->_parent->_right && y->_left->_color == Black
						&& y->_right->_color == Red)
				{
					y->_color = Red;
					y->_right->color = Black;
					left_rotation(y);
				}
			}
			delete_case6(target);
		};
		void	delete_case6(nodeptr target)
		{
			nodeptr	y = sibling(target);
			y->_color = target->_parent->_color;
			target->_parent->_color = Black;
			if (target == target->_parent->_left)
			{
				y->_right->_color = Black;
				left_rotation(target->_parent);
			}
			else
			{
				y->_left->_color = Black;
				right_rotation(target->_parent);
			}
		};
	};
};

#endif
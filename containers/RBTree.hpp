#ifndef RBTREE_HPP
# define RBTREE_HPP

# include <memory>
# include <iostream>
# include "utils.hpp"
# include "pair.hpp"

namespace ft
{
	// x로부터 하위 노드의 유효성 검사, black 갯수 확인.
	template <class nodeptr>
	unsigned	tree_sub_invariant(nodeptr x)
	{
		if (x == m_nullptr) // 리프노드에 도달했을때
			return (1);
		else if (x->_left != m_nullptr && x->_left->_parent != x)	// 유효성 검사
			return (0);
		else if (x->_right != m_nullptr && x->_right->_parent != x)	// 유효성 검사
			return (0);
		else if (x->_left == x->_right && x->_left != m_nullptr)	// 유효성 검사
			return (0);
		else if (!x->_is_black)	// 본인이 Red일 때, 자식노드도 Red일까?
		{
			if (x->_left && !x->_left->_is_black)
				return (0);
			if (x->_right && !x->_right->_is_black)
				return (0);
		}
		// 재귀를 통한 자식의 black 갯수 확인.
		unsigned	h = tree_sub_invariant(x->_left);
		if (h == 0)
			return (0);
		if (h != tree_sub_invariant(x->_right))
			return (0);
		return (h + x->_is_black);
	};

	// root로부터 하위 노드의 유효성 검사.
	template <class nodeptr>
	bool	tree_invariant(nodeptr root)
	{
		if (root == m_nullptr)
			return (true);
		else if (root->_parent == m_nullptr)
			return (false);
		else if (!tree_is_left_child(root))
			return (false);
		else if (!root->_is_black)
			return (false);
		else
			return (tree_sub_invariant(root) != 0);
	};

	template <class nodeptr>
	inline nodeptr	tree_min(nodeptr x) _NOEXCEPT
	{
		while (x->_left != m_nullptr)
			x = x->_left;
		return (x);
	};

	template <class nodeptr>
	inline nodeptr	tree_max(nodeptr x) _NOEXCEPT
	{
		while (x->_right != m_nullptr)
			x = x->_right;
		return (x);
	};

	template <class nodeptr>
	inline nodeptr	tree_next(nodeptr x) _NOEXCEPT
	{
		if (x->_right != m_nullptr)
			return (tree_min(x->_right));
		while (!tree_is_left_child(x))
			x = x->parent_unsafe();
		return (x->parent_unsafe());
	};

	template <class end_nodeptr, class nodeptr>
	inline end_nodeptr	tree_next_iter(nodeptr x) _NOEXCEPT
	{
		if (x->_right != m_nullptr)
			return (static_cast<end_nodeptr>(tree_min(x->_right)));
		while (!tree_is_left_child(x))
			x = x->parent_unsafe();
		return (static_cast<end_nodeptr>(x->_parent));
	};

	template <class end_nodeptr, class nodeptr>
	inline nodeptr	tree_prev_iter(end_nodeptr x) _NOEXCEPT
	{
		if (x->_left != m_nullptr)
			return (tree_max(x->_left));
		nodeptr	temp = static_cast<nodeptr>(x);
		while (tree_is_left_child(temp))
			temp = temp->parent_unsafe();
		return (temp->parent_unsafe());
	};

	template <class nodeptr>
	nodeptr	tree_leaf(nodeptr x) _NOEXCEPT
	{
		while (true)
		{
			if (x->_left != m_nullptr)
			{
				x = x->_left;
				continue;
			}
			if (x->_right != m_nullptr)
			{
				x = x->_right;
				continue;
			}
			break;
		}
		return (x);
	}

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
			: _val(origin._val), _color(Red), _parent(origin._parent), _left(origin._left), _right(origin._right)
			{}
		};
		typedef node*		nodeptr;
	protected:
		nodeptr	_root;
	public:
		tree_base(void) : tree_base(m_nullptr) {};
		tree_base(const tree_base& origin) { this->_root = new node(origin); };
		tree_base	&operator=(const tree_base& origin)
		{
			if (this != &origin)
				this->_root = new node(origin);
			return (*this);
		};
		virtual ~tree_base(void) { all_clear(); };

		// Rotation
		void	left_rotation(nodeptr x)
		{
			nodeptr	y = x->_right;
			x->_right = y->_left;				// change child
			if (y->left != m_nullptr)
				y->_left->_parent = x;
			y->_left = x;
			y->_parent = x->_parent;			// change parent
			if (x->_parent == m_nullptr)		// x가 root일 때
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
			if (y->_left != m_nullptr)
				y->_left->_parent = y;
			x->_right = y;
			x->_parent = y->_parent;
			if (y->_parent == m_nullptr)
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
			nodeptr	p = m_nullptr;
			nodeptr	c = _root;
			while (c == m_nullptr)
			{
				p = c;
				if (Comp(target->_val, c->_val))
					c = c->_right;
				else
					c = c->_left;
			}
			target->_parent = p;
			if (p == m_nullptr)
				_root = target;
			else if (Comp(target->_val, p->_val))
				p->_right = target;
			else
				p->_left = target;
			target->_left = m_nullptr;
			target->_right = m_nullptr;
			target->_color = Red;
			insert_fixup(target);
		};
		void	insert_fixup(nodeptr target)
		{

		};
	};
	
};

#endif
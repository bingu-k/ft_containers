#ifndef RBTREE_HPP
# define RBTREE_HPP

#include <memory>
#include "utils.hpp"

namespace ft
{
	enum color
	{
		Red,
		Black
	};

	template <class K, class V>
	struct node
	{
		K		_key = m_nullptr;
		V		_value = m_nullptr;
		color	_color = Black;
		node*	_parent = m_nullptr;
		node*	_right = m_nullptr;
		node*	_left = m_nullptr;
	};

	template <class K, class V, class alloc = std::allocator< node<K, V> > >
	class RBTree
	{
	public:
		typename K								key_type;
		typename V								value_type;
		typename node<key_type, value_type>*	nodeptr;
		typename alloc							allocate_type;
	private:
		nodeptr			_root;
		allocate_type	_alloc;

	public:
		RBTree(const allocate_type& alloc = allocate_type())
		: _alloc(alloc), _root(m_nullptr) {};
		~RBTree(void)
		{ clear_all(_root); };

		//--------------------------Utilitys--------------------------
		nodeptr	make_node(key_type key, value_type val)
		{
			nodeptr	temp_node = this->make_node();
			temp_node->_key = key;
			temp_node->_value = val;
			temp_node->_color = Red;
			temp_node->_parent = m_nullptr;
			temp_node->_right = m_nullptr;
			temp_node->_left = m_nullptr;
			return (temp_node);
		};

		void	clear_all(nodeptr curr_node)
		{
			if (curr_node == m_nullptr)
				return ;
			clear_all(curr_node->_right);
			clear_all(curr_node->_left);
			_alloc.deallocate(curr_node);
		};

		void	change_left_child(nodeptr left_child = make_node())
		{ this->_root->_left = left_child; };
		
		void	change_right_child(nodeptr right_child = make_node())
		{ this->_root->_right = right_child; };
		
		void	change_color(nodeptr _root)
		{
			if (this->_root->_color == Red)
				this->_root->_color = Black;
			else
				this->_root->_color = Red;
		};

		//--------------------------Rotation--------------------------
		void	left_rotation(nodeptr target)
		{
			nodeptr	temp = target->_right;
			target->_right = temp->_left;
			if (temp->_left != m_nullptr)
				temp->_left->_parent = target;
			temp->_parent = target->_parent;
			if (target->_parent == m_nullptr)
				this->_root = temp;
			else if (target == target->_parent->_left)
				target->_parent->_left = temp;
			else
				target->parent->_right = temp;
			temp->_left = target;
			target->_parent = temp;
		};
		void	right_rotation(nodeptr target)
		{
			nodeptr	temp = target->_left;
			target->_left = temp->_right;
			if (temp->_right != m_nullptr)
				temp->_right->_parent = target;
			temp->_parent = target->_parent;
			if (target->_parent == m_nullptr)
				this->_root = temp;
			else if (target == target->_parent->_right)
				target->_parent->_right = temp;
			else
				target->parent->_left = temp;
			temp->_right = target;
			target->_parent = temp;
		};

		//--------------------------Insert--------------------------
		void	normal_insert(nodeptr root, nodeptr target)
		{
			if (root == m_nullptr)
				this->_root = target;
			else if (root->_key < target->_key)
			{
				if (root->_right == m_nullptr)
					root->_right = target;
				else
					normal_insert(root->_right, target);
			}
			else// if (root->_key > target->_key)
			{
				if (root->_left == m_nullptr)
					root->_left = target;
				else
					normal_insert(root->_left, target);
			}
		};
		void	insert_fixup_case(nodeptr target, nodeptr uncle, nodeptr bro)
		{
			if (uncle->_color == Red)
			{
				target->_parent->_color = Black;
				uncle->_color = Black;
				target->_parent->_parent->_color = Red;
				target = target->_parent->_parent;
			}
			else
			{
				if (target == bro)
				{
					target = target->_parent;
					if (bro == target->_parent->_right)
						left_rotation(target);
					else
						right_rotation(target);
				}
				target->_parent->_color = Black;
				target->_parent->_parent->_color = Red;
				if (bro == target->_parent->_right)
					right_rotation(target);
				else
					left_rotation(target);
			}
		};
		void	insert_fixup(nodeptr target)
		{
			while (target->_parent->_color == Red)
			{
				if (target->_parent == target->_parent->_parent->_left)
					insert_fixup_case(target, target->_parent->_parent->_right, target->_parent->_right);
				else
					insert_fixup_case(target, target->_parent->_parent->_left, target->_parent->_left);
			}
			this->_root->_color = Black;
		};
		void	insert(nodeptr target)
		{
			normal_insert(this->_root, target);
			target->_color = Red;
			target->_r_child = m_nullptr;
			target->_l_child = m_nullptr;
			insert_fixup(target);
		};

	};
};

#endif
#ifndef NODE_HPP
# define NODE_HPP

# include "utils.hpp"
# include "pair.hpp"
# include "pointer.hpp"

namespace ft
{
	typedef enum
	{
		Red,
		Black
	} color_t;

	template <class V>
	struct node
	{

		V		_val = m_nullptr;
		color_t	_color = Red;
		node*	_parent = m_nullptr;
		node*	_left = m_nullptr;
		node*	_right = m_nullptr;
		node(V _val = m_nullptr)
		: _val(_val), _color(Red), _parent(m_nullptr), _left(m_nullptr), _right(m_nullptr)
		{}
		node(const node& origin)
		: _val(origin._val), _color(origin._color), _parent(origin._parent), _left(origin._left), _right(origin._right)
		{}
	};

	//////////////////////////////////////////////////

	// node_traits
		// __tree_key_value_types
			// key와 value 저장해준다.
			// 탬플릿 변수가 하나들어오면 map이 아니다.
	template <class T>
	struct __tree_key_value_types;
	template <class key, class T>
	struct __tree_key_value_types<ft::pair<key, T> >;

		// __tree_node_base_types
			// ????????
	template <class voidptr>
	struct __tree_node_base_types;

		//__tree_map_pointer_types
			// map의 tree 포인터지정
	template <class T, class Allocptr, class KVtypes = __tree_key_value_types<T>,
			bool = KVtypes::__is_map >
	struct __tree_map_pointer_types;
	template <class T, class Allocptr, class KVtypes>
	struct __tree_map_pointer_types<T, Allocptr, KVtypes, true>;

	template <class nodeptr, class node_t = typename pointer_traits<nodeptr>::element_type>
	struct __tree_node_types;
	template <class nodeptr, class T, class voidptr>
	struct __tree_node_types<nodeptr, __tree_node<T, voidptr> >
		: public __tree_node_base_types<voidptr>,
				 __tree_key_value_types<T>,
				 __tree_map_pointer_types<T, voidptr>;
	
	template <class val, class voidptr>
	struct __make_tree_node_types;

	// node
	template <class ptr>
	class __tree_end_node;

	template <class voidptr>
	class __tree_node_base
		: public __tree_node_base_types<voidptr>::__end_node_type;
	
	template <class T, class voidptr>
	class __tree_node : public __tree_node_base<voidptr>;

	template <class Alloc>
	class __tree_node_destructor;
};

#endif
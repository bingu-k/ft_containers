#ifndef UTILS_HPP
# define UTILS_HPP

# include <cstddef>
# include <functional>
# include <memory>
# include "iterator.hpp"

namespace ft
{
	// m_nullptr
	const class nullptr_t
	{
	public:
		template <class T>
		operator T*() const { return 0; }
		template <class T, class U>
		operator T U::*() const { return 0; }
	private:
		void	operator&() const;
	} m_nullptr;
	

	// enable_if :	템플릿의 특수화로 true가 첫 템플릿으로 들어왔을 때, 
	template <bool Cond, class T = void>
	struct enable_if {};
	template <class T>
	struct enable_if<true, T> { typedef T type; };
	
	// is_integral :	해당하는 자료형(정수형)이 아니라면 false
	template <class T>
	struct is_integral_status
	{ static const bool	value_type = false; };
	template <>
	struct is_integral_status<bool>
	{ static const bool	value_type = true; };
	template <>
	struct is_integral_status<char>
	{ static const bool	value_type = true; };
	template <>
	struct is_integral_status<wchar_t>
	{ static const bool	value_type = true; };
	template <>
	struct is_integral_status<char16_t>
	{ static const bool	value_type = true; };
	template <>
	struct is_integral_status<char32_t>
	{ static const bool	value_type = true; };
	template <>
	struct is_integral_status<signed char>
	{ static const bool	value_type = true; };
	template <>
	struct is_integral_status<unsigned char>
	{ static const bool	value_type = true; };
	template <>
	struct is_integral_status<short>
	{ static const bool	value_type = true; };
	template <>
	struct is_integral_status<unsigned short>
	{ static const bool	value_type = true; };
	template <>
	struct is_integral_status<int>
	{ static const bool	value_type = true; };
	template <>
	struct is_integral_status<unsigned int>
	{ static const bool	value_type = true; };
	template <>
	struct is_integral_status<long>
	{ static const bool	value_type = true; };
	template <>
	struct is_integral_status<unsigned long>
	{ static const bool	value_type = true; };
	template <>
	struct is_integral_status<long long>
	{ static const bool	value_type = true; };
	template <>
	struct is_integral_status<unsigned long long>
	{ static const bool	value_type = true; };

	template <typename T>
	struct	is_integral : public is_integral_status<T> {};

	// equal :	모든 1의 인덱스에 따라 1의 내부값와 2의 내부값이 같아야 한다.
	//			1의 size <= 2의 size
	template <class T1, class T2 = T1>
	struct is_equal
	{
		bool	operator()(const T1& x, const T1& y) const
		{ return (x == y); };
		bool	operator()(const T1& x, const T2& y) const
		{ return (x == y); };
		bool	operator()(const T2& x, const T1& y) const
		{ return (x == y); };
		bool	operator()(const T2& x, const T2& y) const
		{ return (x == y); };
	};
	template <class T>
	struct is_equal<T, T>
	{
		bool	operator()(const T& x, const T& y) const
		{ return (x == y); };
	};
	template <class T>
	struct is_equal<const T, T>
	{
		bool	operator()(const T& x, const T& y) const
		{ return (x == y); };
	};
	template <class T>
	struct is_equal<T, const T>
	{
		bool	operator()(const T& x, const T& y) const
		{ return (x == y); };
	};

	template <class InputIter1, class InputIter2, class BinaryPredicate>
	bool equal (InputIter1 first1, InputIter1 last1,
				InputIter2 first2, InputIter2 last2, BinaryPredicate pred)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (!pred(*first1, *first2))
				return (false);
			++first1;
			++first2;
		}
		if (first1 == last1 && first2 != last2)
			return (false);
		else if (first1 != last1 && first2 == last2)
			return (false);
		else
			return (true);
	};
	template <class InputIter1, class InputIter2>
	bool	equal(InputIter1 first1, InputIter1 last1, InputIter2 first2, InputIter2 last2)
	{
		typedef typename	iterator_traits<InputIter1>::value_type v1;
		typedef typename	iterator_traits<InputIter2>::value_type v2;
		return (ft::equal(first1, last1, first2, last2, ft::is_equal<v1, v2>()));
	};

	// lexicographical_compare :	모든 1의 인덱스에 따라 1의 내부값이 2의 내부값보다 작아야 함.
	//								1의 size < 2의 size
	template <class T1, class T2 = T1>
	struct less
	{
		bool	operator()(const T1& x, const T1& y) const
		{ return (x < y); };
		bool	operator()(const T1& x, const T2& y) const
		{ return (x < y); };
		bool	operator()(const T2& x, const T1& y) const
		{ return (x < y); };
		bool	operator()(const T2& x, const T2& y) const
		{ return (x < y); };
	};
	template <class T>
	struct less<T, T>
	{
		bool	operator()(const T& x, const T& y) const
		{ return (x < y); };
	};
	template <class T>
	struct less<const T, T>
	{
		bool	operator()(const T& x, const T& y) const
		{ return (x < y); };
	};
	template <class T>
	struct less<T, const T>
	{
		bool	operator()(const T& x, const T& y) const
		{ return (x < y); };
	};
	template <class InputIter1, class InputIter2, class Compare>
	bool lexicographical_compare (InputIter1 first1, InputIter1 last1,
                                InputIter2 first2, InputIter2 last2, Compare comp)
	{
		for (; first2 != last2; ++first1, (void) ++first2)
		{
			if (first1 == last1 || comp(*first1, *first2))
				return (true);
			if (comp(*first2, *first1))
				return (false);
		}
		return (false);
	};
	template <class InputIter1, class InputIter2>
	bool lexicographical_compare (InputIter1 first1, InputIter1 last1,
                                InputIter2 first2, InputIter2 last2)
	{
		typedef typename	iterator_traits<InputIter1>::value_type	v1;
		typedef typename	iterator_traits<InputIter2>::value_type	v2;
		return ( ft::lexicographical_compare(first1, last1, first2, last2, ft::less<v1, v2>()) );
	};
	// rebind의 행동
		// allocator에서는 탬플릿 변수 하나를 갖고와서
		// 해당 탬플릿 변수를 allocator에 적용시켜 other로 typedef함.
		// typedef allocator<V>	other
		// pointer에서도 탬플릿 변수 하나를 갖고와서
		// 해당 탬플릿 변수의 포인터를 other로 적용하여 typedef함.
		// typedef V*	other
	// rebind의 이유
	// 처음에 Allocator를 받아올때 탬플릿 변수는 pair로 받는다.
	// 그렇게 되면 우리가 정의한 Allocator는 pair에 관한 할당을 해주는데
	// map은 내부가 tree로 이뤄져있기 때문에 우리는 node에 대한 할당을 해주어야한다.
	// 그렇게 되면 우리가 node에 대한 할당은 rebind를 통해 node에 관한 Allocator를 생성하고
	// 생성된 Allocator로 할당을 해주는 상황이 되야하기 때문에 rebind를 사용해야한다.

	// pair
	template <class T1, class T2>
	struct pair
	{
		public:
			// Typedef
			typedef T1	first_type;
			typedef T2	second_type;

			// Variable
			first_type	first;
			second_type	second;

			// Constructor
			pair(void) : first(), second() {};
			pair(first_type const& a, second_type const& b)
			: first(a), second(b) {};
			template <class U, class V>
			pair(pair<U, V> const& pr) : first(pr.first), second(pr.second) {};

			// Assign Operator
			pair&	operator=(pair const& pr)
			{
				this->first = pr.first;
				this->second = pr.second;
				return (*this);
			};
	};

	// Relational Operators
	template <class T1, class T2>
	bool	operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ return (lhs.first==rhs.first && lhs.second==rhs.second); };
	template <class T1, class T2>
	bool	operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ return !(lhs == rhs); };
	template <class T1, class T2>
	bool	operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second)); };
	template <class T1, class T2>
	bool	operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ return !(rhs > lhs); };
	template <class T1, class T2>
	bool	operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ return (rhs < lhs); };
	template <class T1, class T2>
	bool	operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ return !(lhs < rhs); };

	// Make Pair
	template <class T1, class T2>
	inline pair<T1, T2> make_pair (T1 x, T2 y)
	{ return (pair<T1, T2>(x, y)); };

	// swap
	template <class T>
	void	swap_something(T& a, T& b)
	{
		T	temp = a;
		a = b;
		b = temp;
	};

	// value compare
	template <class Key, class Value, class _Compare>
	class _value_compare : private _Compare			// value_compare 상속
	{
		_Compare	comp;
		public:
			_value_compare() : comp() {};
			_value_compare(_Compare c) : comp(c) {};
			
			const _Compare&	key_comp() const { return (*this); };

			bool	operator()(const Value& x, const Value& y) const
			{ return (comp(x.first, y.first)); };
			bool	operator()(const Key& x, const Value& y) const
			{ return (comp(x, y.first)); };
			bool	operator()(const Value& x, const Key& y) const
			{ return (comp(x.first, y)); };

	};

	// node
	enum node_color
	{
		Black,
		Red
	};
	template <class T>
	struct node
	{
		T			_val;
		node_color	_color;
		node<T>*	_parent;
		node<T>*	_left;
		node<T>*	_right;
		
		node(T val = T()) : _val(val)
		{
			_color = Red;
			_parent = m_nullptr;
			_left = m_nullptr;
			_right = m_nullptr;
		};
	};
	template <class nodeptr>
	bool	is_nil(nodeptr node)
	{
		if (node->_left == m_nullptr && node->_right == m_nullptr)
			return (true);
		return (false);
	};
}

#include <__tree>

#endif
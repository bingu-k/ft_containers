#ifndef UTILS_HPP
# define UTILS_HPP

# include <cstddef>
# include <functional>

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
				InputIter2 first2, BinaryPredicate pred)
	{
		while (first1 != last1)
		{
			if (!pred(*first1, *first2))
				return (false);
			++first1;
			++first2;
		}
		return (true);
	};
	template <class InputIter1, class InputIter2>
	bool equal (InputIter1 first1, InputIter1 last1, InputIter2 first2)
	{
		typedef typename	iterator_traits<InputIter1>::value_type v1;
		typedef typename	iterator_traits<InputIter2>::value_type v2;
		return (ft::equal(first1, last1, first2, ft::is_equal<v1, v2>()));
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

	// --------------------------map--------------------------
	
	// __void_t
	// void type을 표현해주기 위함.
	// 걍 void를 쓰면 될 것을 왜 쓰냐?
	// 탬플릿 변수를 하나 가져오는데 이 변수가 없으면 에러가 날 것.
	template <class>
	struct _void_t { typedef void type; };

	// rebind
	template <class T, class U, bool = _has_rebind<T, U>::value>
	struct _has_rebind_other
	{
		
	};
	
	template <class T, class U, bool = ft::_has_rebind_other<T, U>::value >
	struct _allocator_traits_rebind
	{ typeef typename T::template rebind<U>::other type; };
	template <class alloc, class T>
	struct rebind_alloc
	{ typedef typename ft::_allocator_traits_rebind<alloc, T>::type other; };

	// has_element_type
	// element_type가 존재하는지 확인
	template <class T, class = void>
	struct has_element_type
	{ static const bool& type = false; };
	template <class T, typename _void_t<typename T::element_type>::type>
	struct has_element_type
	{ static const bool& type = true; };

	// pointer_traits_element_type
	// element_type을 추출하기 위함.
	template <class ptr, bool = has_element_type<ptr>::type>
	struct pointer_traits_element_type;
	template <class ptr>
	struct pointer_traits_element_type<ptr, true>
	{ typedef typename ptr::element_type	type; };
	template <class ptr>
	struct pointer_traits_element_type<ptr, false>
	{ typedef ptr	type; };

	// rebind의 이유
	// map은 pair로 key와 value를 갖는데
	// key가 다르면 문제가 생기지만
	// value가 다를때는 문제가 생기진 않는다.
	// 허나, 포인터를 그대로 받아오는 상황에서는 문제가 생긴다.
	// 원래의 key, value로 typedef를 이용해 포인터를 지정했는데
	// 다른 타입의 value를 넣어버린다면 rebind를 이용해서 포인터를 만들어줘야한다.
	template <class T, class U>
	struct pointer_traits_rebind
	{ typedef T::template rebind<U>::other	type; };

	template <class from, class T>
	struct rebind_pointer
	{ typedef pointer_traits<from>::template rebind<T>::other	type; };
}

#endif
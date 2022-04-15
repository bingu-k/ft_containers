#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>
# include <exception>

namespace ft
{
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
		for (; first1 != last1; ++first1, (void) ++first2)
			if (!pred(*first1, *first2))
				return (false);
		return (ture);
	};
	template <class InputIter1, class InputIter2>
	bool equal (InputIter1 first1, InputIter1 last1, InputIter2 first2)
	{
		typedef typename	iterator::traits<InputIter1>::value_type v1;
		typedef typename	iterator::traits<InputIter2>::value_type v2;
		return (equal(first1, last1, first2, is_equal<v1, v2>()));
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
		typedef typename	iterator::traits<InputIter1>::value_type v1;
		typedef typename	iterator::traits<InputIter2>::value_type v2;
		return (lexicographical_compare (InputIter1 first1, InputIter1 last1,
                                InputIter2 first2, InputIter2 last2, less<v1, v2>()););
	};
}

#endif
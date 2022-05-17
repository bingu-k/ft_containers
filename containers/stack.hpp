#ifndef STACK_HPP
# define STACK_HPP

/*
namespace ft
{
	template <class T, class Container = vector<T> >
	class stack
	{
	public:
		// Typedef Member types
		typedef T				value_type;
		typedef Container		container_type;
		typedef unsigned int	size_type;
	private:
		container_type	c;
	public:
		// Constructor
		explicit stack(const container_type& ctnr = container_type());
		// Destructor
		~stack();

		// Member Fucntion
		bool				empty(void) const;
		size_type			size(void) const;
		value_type&			top(void);
		const value_type&	top(void) const;
		void				push(const value_type& val);
		void				pop(void);
		template <class _T, class _Container>
		friend bool	operator==
		(const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs);
		template <class _T, class _Container>
		friend bool	operator<
		(const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs);
	
	};
	template <class T, class Container>
	bool	operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs);
	template <class T, class Container>
	bool	operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs);
	template <class T, class Container>
	bool	operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs);
	template <class T, class Container>
	bool	operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs);
	template <class T, class Container>
	bool	operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs);
	template <class T, class Container>
	bool	operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs);
}
*/

# include "vector.hpp"

namespace ft
{
	template <class T, class Container = vector<T> >
	class stack
	{
	public:
		// Typedef Member types
		typedef T				value_type;
		typedef Container		container_type;
		typedef unsigned int	size_type;
	private:
		container_type	c;
	public:
		// Constructor
		explicit stack(const container_type& ctnr = container_type())
		: c(ctnr) {};
		// Destructor
		~stack() {};

		// Member Fucntion
		bool				empty(void) const
		{ return (c.empty()); };
		size_type			size(void) const
		{ return (c.size()); };
		value_type&			top(void)
		{ return (c.back()); };
		const value_type&	top(void) const
		{ return (c.back()); };
		void				push(const value_type& val) { c.push_back(val); };
		void				pop(void) { c.pop_back(); };
		template <class _T, class _Container>
		friend bool	operator==
		(const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs);
		template <class _T, class _Container>
		friend bool	operator<
		(const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs);
	
	};
	template <class T, class Container>
	bool	operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return (lhs.c == rhs.c); };

	template <class T, class Container>
	bool	operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return !(lhs == rhs); };

	template <class T, class Container>
	bool	operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return (lhs.c < rhs.c); };

	template <class T, class Container>
	bool	operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return !(rhs < lhs); };
	
	template <class T, class Container>
	bool	operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return (rhs < lhs); };

	template <class T, class Container>
	bool	operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{ return !(lhs < rhs); };
}

#endif
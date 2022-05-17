#ifndef	VECTOR_HPP
# define VECTOR_HPP

/*
namespace ft
{
	// Error classes
	template <bool>
	class vector_common
	{
	protected:
		vector_common();
		void	throw_length_error() const;
		void	throw_out_of_range() const;
	};

	// Vector Base
	template <class T, class Allocator>
	class vector_base
		: protected vector_common<true>
	{
	public:
		typedef Allocator									allocator_type;
		typedef typename allocator_type::size_type			size_type;
	protected:
		typedef T											value_type;
		typedef value_type&									reference;
		typedef const value_type&							const_reference;
		typedef typename allocator_type::difference_type	difference_type;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef pointer										iterator;
		typedef const_pointer								const_iterator;

		pointer			_begin;
		pointer			_end;
		pointer			_end_cap;
		allocator_type	_alloc;

		allocator_type&			__alloc();
		const allocator_type&	__alloc() const;
		pointer&				__end_cap();
		const pointer&			__end_cap() const;

		vector_base(allocator_type alloc = allocator_type());

		void	_clear(void);
		void	clear_all(void);
		size_type	_capacity(void) const;

		template <class iterator>
		void	copy_range(pointer &start, iterator input_begin, iterator input_end
						, typename ft::enable_if<!is_integral<iterator>::value_type, iterator>::type* = m_nullptr);
		template <class iterator>
		void	copy_limit_range(pointer &start, iterator input_begin, iterator input_end, size_type limit);
		void	copy_range(pointer &start, size_type n, value_type val);
		void	allocate_size(size_type n);
		size_type	insert_choose_capacity(size_type curr_size, size_type curr_cap, size_type n);
		void	_swap(pointer &a, pointer &b);
	};

	template < class T, class Alloc = std::allocator<T> >
	class vector : private vector_base<T, Alloc>
	{
	public:
		typedef T											value_type;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_poiner;
		typedef typename allocator_type::difference_type	difference_type;
		typedef typename allocator_type::size_type			size_type;
		typedef ft::vector_iterator<T>						iterator;
		typedef ft::vector_iterator<const T>				const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

		// Construct
		explicit vector(const allocator_type& alloc = allocator_type())
		: vector_base<T, allocator_type>(alloc) {};
		explicit vector(size_type n, const value_type& val = value_type()
						, const allocator_type& alloc = allocator_type());
		template <class InputIterator>
		vector(InputIterator first, InputIterator last
			, const allocator_type& alloc = allocator_type()
			, typename ft::enable_if<!is_integral<InputIterator>::value_type, InputIterator>::type* = m_nullptr);
		vector(const vector& x) : vector_base<T, allocator_type>(x.__alloc());

		// Destruct
		~vector(void);

		// Substitude Operator
		vector&	operator=(const vector& x);

		// Iterator
		iterator				begin(void);
		const_iterator			begin(void) const;
		iterator				end(void);
		const_iterator			end(void) const;
		reverse_iterator		rbegin(void);
		const_reverse_iterator	rbegin(void) const;
		reverse_iterator		rend(void);
		const_reverse_iterator	rend(void) const;

		// Capacity
		size_type		size(void) const;
		size_type		max_size(void) const;
		void			resize(size_type n, value_type val = value_type());
		size_type		capacity(void) const;
		bool			empty(void) const;
		void			reserve(size_type n);

		// Element Access
		reference		operator[](size_type n);
		const_reference	operator[](size_type n) const;
		reference		at(size_type n);
		const_reference	at(size_type n) const;
		reference		front(void);
		const_reference	front(void) const;
		reference		back(void);
		const_reference	back(void) const;

		// Modifiers
		template <class InputIterator>
		void		assign(InputIterator first, InputIterator last
						, typename ft::enable_if<!is_integral<InputIterator>::value_type, InputIterator>::type* = m_nullptr);
		void		assign(size_type n, const value_type& val);
		void		push_back(const value_type& val);
		void		pop_back(void);
		iterator	insert(iterator position, const value_type& val);
		void		insert(iterator position, size_type n, const value_type& val);
		template <class InputIterator>
		void		insert(iterator position, InputIterator first, InputIterator last
						, typename ft::enable_if<!is_integral<InputIterator>::value_type, InputIterator>::type* = m_nullptr);
		iterator erase (iterator position);
		iterator erase (iterator first, iterator last);
		void		swap(vector& x);
		void		clear(void);

		// Allocator
		allocator_type	get_allocator(void) const;
	};

	// Relational Operators
	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);
	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y);
};
*/

# include <exception>
# include <memory>
# include "vector_iterator.hpp"
# include "reverse_iterator.hpp"

namespace ft
{
	// Error classes
	template <bool>
	class vector_common
	{
	protected:
		vector_common() {};
		void	throw_length_error() const
		{ throw (std::length_error("vector")); };
		void	throw_out_of_range() const
		{ throw (std::out_of_range("vector")); };
	};

	// Vector Base
	template <class T, class Allocator>
	class vector_base
		: protected vector_common<true>
	{
	public:
		typedef Allocator									allocator_type;
		typedef typename allocator_type::size_type			size_type;
	protected:
		typedef T											value_type;
		typedef value_type&									reference;
		typedef const value_type&							const_reference;
		typedef typename allocator_type::difference_type	difference_type;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef pointer										iterator;
		typedef const_pointer								const_iterator;

		pointer			_begin;
		pointer			_end;
		pointer			_end_cap;
		allocator_type	_alloc;

		allocator_type&	__alloc() { return (_alloc); };
		const allocator_type&	__alloc() const { return (_alloc); };
		pointer&	__end_cap() { return (_end_cap); };
		const pointer&	__end_cap() const { return (_end_cap); };

		vector_base(allocator_type alloc = allocator_type())
		: _begin(0), _end(0), _end_cap(0), _alloc(alloc) {};

		void	_clear(void)
		{
			pointer	start = this->_begin;
			while (start != this->_end)
				this->_alloc.destroy(start++);
			this->_end = this->_begin;
		};

		void	clear_all(void)
		{
			if (this->_begin != 0)
			{
				_clear();
				this->_alloc.deallocate(this->_begin, _capacity());
				this->_begin = 0;
				this->_end = 0;
				this->_end_cap = 0;
			}
		};

		size_type	_capacity(void) const { return (this->_end_cap - this->_begin); };

		template <class iterator>
		void	copy_range(pointer &start, iterator input_begin, iterator input_end
						, typename ft::enable_if<!is_integral<iterator>::value_type, iterator>::type* = m_nullptr)
		{
			while (input_begin != input_end)
				this->_alloc.construct(start++, *input_begin++);
		};

		template <class iterator>
		void	copy_limit_range(pointer &start, iterator input_begin, iterator input_end, size_type limit)
		{
			size_type	idx = 0;
			while (idx++ != limit && input_begin != input_end)
				this->_alloc.construct(start++, *input_begin++);
		};

		void	copy_range(pointer &start, size_type n, value_type val)
		{
			for (size_type i = 0; i < n; i++)
				this->_alloc.construct(start++, val);
		};

		void	allocate_size(size_type n)
		{
			this->_begin = this->_alloc.allocate(n);
			this->_end = this->_begin;
			this->_end_cap = this->_begin + n;
		};

		size_type	insert_choose_capacity(size_type curr_size, size_type curr_cap, size_type n)
		{
			if (curr_cap == 0)						//초기 모델
				return (n);
			else if (n + curr_size < curr_cap)		//수용 가능 모델
				return (curr_cap);
			else if (n + curr_size < 2 * curr_cap)	//수용 불가, 2배 cap보다 작은 모델
				return (2 * curr_cap);
			else// if (2 * curr_cap < n + curr_size)	//수용 불가, 2배 cap보다 큰 모델
				return (n + curr_size);
		};

		void	_swap(pointer &a, pointer &b)
		{
			pointer	temp = a;
			a = b;
			b = temp;
		};
	};

	template < class T, class Alloc = std::allocator<T> >
	class vector : private vector_base<T, Alloc>
	{
	public:
		typedef T											value_type;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_poiner;
		typedef typename allocator_type::difference_type	difference_type;
		typedef typename allocator_type::size_type			size_type;
		typedef ft::vector_iterator<T>						iterator;
		typedef ft::vector_iterator<const T>				const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

		// Construct
		explicit vector(const allocator_type& alloc = allocator_type())
		: vector_base<T, allocator_type>(alloc) {};
		explicit vector(size_type n, const value_type& val = value_type()
						, const allocator_type& alloc = allocator_type())
		: vector_base<T, allocator_type>(alloc)
		{
			this->allocate_size(n);
			this->copy_range(this->_end, n, val);
		};
		template <class InputIterator>
		vector(InputIterator first, InputIterator last
			, const allocator_type& alloc = allocator_type()
			, typename ft::enable_if<!is_integral<InputIterator>::value_type, InputIterator>::type* = m_nullptr)
		: vector_base<T, allocator_type>(alloc)
		{
			size_type	n = static_cast<size_type>(ft::distance(first, last));
			this->allocate_size(n);
			this->copy_range(this->_end, first, last);
		};
		vector(const vector& x) : vector_base<T, allocator_type>(x.__alloc())
		{
			this->allocate_size(x.capacity());
			this->copy_range(this->_end, x.begin(), x.end());
		};

		// Destruct
		~vector(void) { this->clear_all(); };

		// Substitude Operator
		vector&	operator=(const vector& x)
		{
			if (this != &x)
			{
				if (capacity() != 0)
					this->clear_all();
				this->allocate_size(x.capacity());
				this->copy_range(this->_end, x.begin(), x.end());
			}
			return (*this);
		};

		// Iterator
		iterator				begin(void) { return (iterator(this->_begin)); };
		const_iterator			begin(void) const { return (const_iterator(this->_begin)); };
		iterator				end(void) { return (iterator(this->_end)); };
		const_iterator			end(void) const { return (const_iterator(this->_end)); };
		reverse_iterator		rbegin(void) { return (reverse_iterator(end())); };
		const_reverse_iterator	rbegin(void) const { return (reverse_iterator(end())); };
		reverse_iterator		rend(void) { return (reverse_iterator(begin())); };
		const_reverse_iterator	rend(void) const { return (reverse_iterator(begin())); };

		// Capacity
		size_type		size(void) const { return (static_cast<size_type>(this->_end - this->_begin)); };
		size_type		max_size(void) const { return (this->__alloc().max_size()); };
		void			resize(size_type n, value_type val = value_type())
		{
			if (n < 0 || n > max_size())
				this->throw_length_error();
			else
			{
				size_type	change_cap = n;
				pointer		change_begin = this->__alloc().allocate(change_cap);
				pointer		change_end  = change_begin;
				pointer		change_end_cap = change_begin + change_cap;
				pointer		start = this->_begin;
				size_type	idx = 0;

				while (idx++ < change_cap)
				{
					if (start == this->_end)
						this->__alloc().construct(change_end++, val);
					else
						this->__alloc().construct(change_end++, *start++);
				}
				this->clear_all();
				this->_begin = change_begin;
				this->_end = change_end;
				this->_end_cap = change_end_cap;
			}
		};
		size_type		capacity(void) const { return (this->_capacity()); };
		bool			empty(void) const { return (size() == 0); };
		void			reserve(size_type n)
		{
			if (n < 0 || n > max_size())
				this->throw_length_error();
			else if (n > capacity())
			{
				pointer		change_begin = this->__alloc().allocate(n);
				pointer		change_end  = change_begin;
				pointer		change_end_cap = change_begin + n;

				this->copy_limit_range(change_end, begin(), end(), size());
				this->clear_all();
				this->_begin = change_begin;
				this->_end = change_end;
				this->_end_cap = change_end_cap;
			}
		};

		// Element Access
		reference		operator[](size_type n) { return (*(this->_begin + n)); };
		const_reference	operator[](size_type n) const { return (*(this->_begin + n)); };
		reference		at(size_type n)
		{
			if (n < 0 || n > max_size() || n > size())
				this->throw_out_of_range();
			return (*(begin() + n));
		};
		const_reference	at(size_type n) const
		{
			if (n < 0 || n > max_size() || n > size())
				this->throw_out_of_range();
			return (*(begin() + n));
		};
		reference		front(void) { return (*(this->_begin)); };
		const_reference	front(void) const { return (*(this->_begin)); };
		reference		back(void) { return (*(this->_end - 1)); };
		const_reference	back(void) const { return (*(this->_end - 1)); };

		// Modifiers
		template <class InputIterator>
		void		assign(InputIterator first, InputIterator last
						, typename ft::enable_if<!is_integral<InputIterator>::value_type, InputIterator>::type* = m_nullptr)
		{
			size_type	n = static_cast<size_type>(ft::distance(first, last));
			if (n < this->capacity())
				n = this->capacity();
			this->clear_all();
			this->allocate_size(n);
			this->copy_range(this->_end, first, last);
		}
		void		assign(size_type n, const value_type& val)
		{
			if (n < 0 || n > max_size())
				this->throw_length_error();
			size_type	prev_n = n;
			if (n < this->capacity())
				n = this->capacity();
			this->clear_all();
			this->allocate_size(n);
			this->copy_range(this->_end, prev_n, val);
		}

		void		push_back(const value_type& val)
		{
			if (this->_end == this->_end_cap)
				reserve(capacity() == 0 ? 1 : 2 * capacity());
			this->__alloc().construct(this->_end++, val);
		};
		void		pop_back(void) { this->__alloc().destroy(this->_end--); };

		iterator	insert(iterator position, const value_type& val)
		{
			size_type	n = 0;
			pointer		res = this->_begin;
			while (res++ != &(*position))
				++n;
			insert(position, 1, val);
			return (iterator(begin() + n));
		};
		void		insert(iterator position, size_type n, const value_type& val)
		{
			if (n == 0)
				return  ;
			size_type	change_cap = this->insert_choose_capacity(size(), capacity(), n);
			pointer		change_begin = this->__alloc().allocate(change_cap);
			pointer		change_end = change_begin;
			pointer		change_end_cap = change_begin + change_cap;
			if (size())
				this->copy_range(change_end, begin(), position);
			this->copy_range(change_end, n, val);
			if (size())
				this->copy_range(change_end, position, end());
			this->clear_all();
			this->_begin = change_begin;
			this->_end = change_end;
			this->_end_cap = change_end_cap;
		};
		template <class InputIterator>
		void		insert(iterator position, InputIterator first, InputIterator last
						, typename ft::enable_if<!is_integral<InputIterator>::value_type, InputIterator>::type* = m_nullptr)

		{
			size_type	n = static_cast<size_type>(ft::distance(first, last));
			if (n == 0)
				return ;
			else
			{
				size_type	change_cap = this->insert_choose_capacity(size(), capacity(), n);
				pointer		change_begin = this->__alloc().allocate(change_cap);
				pointer		change_end = change_begin;
				pointer		change_end_cap = change_begin + change_cap;
				if (size())
					this->copy_range(change_end, begin(), position);
				this->copy_range(change_end, first, last);
				if (size())
					this->copy_range(change_end, position, end());
				this->clear_all();
				this->_begin = change_begin;
				this->_end = change_end;
				this->_end_cap = change_end_cap;
			}
		}

		iterator erase (iterator position)
		{ return(erase(position, position + 1)); };
		iterator erase (iterator first, iterator last)
		{
			pointer	change_begin = this->__alloc().allocate(capacity());
			pointer	change_end = change_begin;
			pointer change_end_cap = change_begin + capacity();
			if (size())
				this->copy_range(change_end, begin(), first);
			pointer	res = change_end;
			if (size())
				this->copy_range(change_end, last, end());
			this->clear_all();
			this->_begin = change_begin;
			this->_end = change_end;
			this->_end_cap = change_end_cap;
			return (iterator(res));
		};

		void		swap(vector& x)
		{
			this->_swap(this->_begin, x._begin);
			this->_swap(this->_end, x._end);
			this->_swap(this->_end_cap, x._end_cap);
			allocator_type	temp_alloc = x.__alloc();
			x.__alloc() = this->__alloc();
			this->__alloc() = temp_alloc;
		};

		void		clear(void) { this->_clear(); };

		// Allocator
		allocator_type	get_allocator(void) const { return (this->__alloc()); };
	};

	// Relational Operators
	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	};

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{ return (!(lhs == rhs)); };

	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end()
										, rhs.begin(), rhs.end()));
	};

	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{ return (!(lhs > rhs)); };

	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(rhs.begin(), rhs.end()
										, lhs.begin(), lhs.end()));
	};

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{ return (!(lhs < rhs)); };

	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{ x.swap(y); };
};

#endif
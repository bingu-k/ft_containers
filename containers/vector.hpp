#ifndef	VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include "vector_iterator.hpp"
# include "reverse_iterator.hpp"

namespace ft
{
	template < class T, class Allocator = std::allocator<T> >
	class vector
	{
	public:
		typedef T											value_type;
		typedef Allocator									allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef ft::vector_iterator<T>						iterator;
		typedef ft::vector_iterator<const T>				const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
		typedef typename allocator_type::difference_type	difference_type;
		typedef typename allocator_type::size_type			size_type;

	private:
		allocator_type	_alloc;
		pointer			_begin;
		pointer			_end;
		pointer			_end_cap;

	public:
		// Constructor
		explicit vector (const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _begin(0), _end(0), _end_cap(0)
		{};

		explicit vector (size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type())
		: _alloc(alloc), _begin(0), _end(0), _end_cap(0)
		{
			if (n < 0)
				throw(std::length_error("vector"));
			_begin = _alloc.allocate(n);
			_end = _begin;
			_end_cap = _begin + n;
			while (n--)
				_alloc.construct(_end++, val);
		};

		// 위의 생성자와 구분하기 위해서 is_intergral을 사용하여 정수 자료형을 제외한다.(SFINAE)
		// iterator의 종류를 구분하여 되는 것과 안되는것을 구분하자.
		// 원본 함수를 보면 is_convertible을 사용하여 변환의 문제로 true or false로 확인한다.
		// 그럼 여기서 상속 구조를 보면 input <- forward <- bidirection <- random access
		// output은 따로 떨어져있다.
		// vector의 iterator는 random access iterator로 output iterator이외는 전부 변환 가능하다.
		template <class InputIter>
		vector (InputIter first, InputIter last, const allocator_type& alloc = allocator_type()
				, typename ft::enable_if<!ft::is_integral<InputIter>::value_type, InputIter>::type* = m_nullptr)
		: _alloc(alloc), _begin(0), _end(0), _end_cap(0)
		{
			difference_type	n = ft::distance(first, last);
			_begin = _alloc.allocate(n);
			_end = _begin;
			_end_cap = _begin + n;
			while (n--)
				_alloc.construct(_end++, *first++);
		};

		vector (const vector& x)
		: _alloc(x._alloc), _begin(0), _end(0), _end_cap(0)
		{ this->insert(begin(), x.begin(), x.end()); };

		~vector()
		{
			this->clear();
			this->_alloc.deallocate(this->_begin, this->capacity());
		};

		// Operator overloading
		vector	&operator=(const vector& x)
		{
			if (this != &x)
			{
				this->clear();
				this->_alloc.deallocate(this->_begin, this->capacity());
				_begin = 0;
				_end = 0;
				_end_cap = 0;
				if (x.size() != 0)
					this->insert(begin(), x.begin(), x.end());
			}
			return (*this);
		}
		

		// Iterators
		iterator				begin(void) { return (iterator(_begin)); };
		const_iterator			begin(void) const { return (const_iterator(_begin)); };
		iterator				end(void) { return (iterator(_end)); };
		const_iterator			end(void) const { return (const_iterator(_end)); };
		reverse_iterator		rbegin(void) { return (reverse_iterator(end())); };
		const_reverse_iterator	rbegin(void) const { return (reverse_iterator(end())); };
		reverse_iterator		rend(void) { return (reverse_iterator(begin())); };
		const_reverse_iterator	rend(void) const { return (reverse_iterator(begin())); };

		// Capacity
		size_type		size(void) const { return (static_cast<size_type>(_end - _begin)); };
		size_type		max_size(void) const { return (_alloc.max_size()); };

		// 동작 : 현재 vector의 size를 재조정해준다.
		// 에러(n)
			// 음수, max_size보다 크다	: length_error
			// 현재 size보다 작다		: begin + n부터 end까지 삭제 후 end를 begin + n으로 재지정
			// 현재 size와 같다			: 아무 동작 하지 않는다.
			// 현재 size보다 크다		: capacity를 바꿔준다. 즉, 재할당 후 복사
		void			resize (size_type n, value_type val = value_type())
		{
			if (n < 0 || n > max_size())
				throw(std::length_error("vector"));
			else
			{
				size_type	change_cap = 0;
				if (n < capacity())
					change_cap = capacity();
				else if (n < 2 * capacity())
					change_cap = 2 * capacity();
				else
					change_cap = n;
				size_type	idx = 0;
				vector		res_vec(this->_alloc);
				res_vec._begin = _alloc.allocate(change_cap);
				res_vec._end = res_vec._begin;
				res_vec._end_cap = res_vec._begin + change_cap;
				iterator	start = begin();
				while (idx < n && start != end())
				{
					_alloc.construct((res_vec._end)++, *start);
					++idx;
					++start;
				}
				while (idx++ < n)
					res_vec.push_back(val);
				this->swap(res_vec);
			}
		};

		size_type		capacity(void) const { return (_end_cap - _begin); };
		bool			empty(void) const { return (_begin == _end); };

		// 동작 : vector의 capacity를 변경시켜준다.
		// 예외 (n)
			// 음수, max_size보다 크다		: length_error
			// 현재 size보다 작거나 같다	  : 아무 동작 하지 않는다.
			// 현재 size보다 크다			: capacity를 바꿔준다. 즉, 재할당 후 복사
		void			reserve (size_type n)
		{
			if (n < 0 || n > max_size())
				throw(std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size"));
			else if (n > capacity())
			{
				pointer		change_begin = _alloc.allocate(n);
				pointer		change_end = change_begin;
				pointer		change_end_cap = change_begin + n;
				pointer		prev_begin = _begin;
				if (size() != 0)
					while (prev_begin != _end)
						_alloc.construct(change_end++, *prev_begin++);
				if (capacity() != 0)
				{
					clear();
					_alloc.deallocate(_begin, capacity());
				}
				_begin = change_begin;
				_end = change_end;
				_end_cap = change_end_cap;
			}
		}

		// Element access
		reference		operator[] (size_type n) { return (*(_begin + n)); };
		const_reference	operator[] (size_type n) const { return (*(_begin + n)); };

		reference		at(size_type n)
		{
			if (n > size())
				throw(std::out_of_range("vector"));
			return (*(begin() + n));
		};
		const_reference	at(size_type n) const
		{
			if (n > size())
				throw(std::out_of_range("vector"));
			return (*(this->begin() + n));
		};

		reference		front(void) { return (*_begin); };
		const_reference	front(void) const { return (*_begin); };
		reference		back(void) { return (*(_end - 1)); };
		const_reference	back(void) const { return (*(_end - 1)); };

		// Modifiers
		template <class InputIter>
		void	assign(InputIter first, InputIter last
						, typename ft::enable_if<!ft::is_integral<InputIter>::value_type, InputIter>::type* = m_nullptr)
		{
			size_type	n = static_cast<size_type>(ft::distance(first, last));
			
			clear();
			if (n < 0 || n > max_size())
				throw(std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size"));
			else
			{
				if (capacity() < n)
				{
					_alloc.deallocate(_begin, capacity());
					_begin = _alloc.allocate(n);
					_end_cap = _begin + n;
				}
				_end = _begin;
				while (first != last)
					_alloc.construct(_end++, *first++);
			}
		};
		void	assign(size_type n, const value_type& val)
		{
			clear();
			if (n < 0 || n > max_size())
				throw(std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size"));
			else
			{
				if (capacity() < n)
				{
					_alloc.deallocate(_begin, capacity());
					_begin = _alloc.allocate(n);
					_end_cap = _begin + n;
				}
				_end = _begin;
				for (size_type i = 0; i < n; i++)
					_alloc.construct(_end++, val);
			}
		};

		// 초기값은 0, 추가되면 1, 계속 추가되면 2의 지수승으로 커진다.
		void	push_back(const value_type& val)
		{
			if (size() == capacity())
				reserve(capacity() == 0 ? 1 : capacity() * 2);
			_alloc.construct(_end++, val);
		};

		void	pop_back(void) { _alloc.destroy(_end--); };

		// 동작 : 해당 위치에 val을 추가한다. capacity를 넘어갈 경우 재할당.
		// 예외(position)
			// begin보다 작은 위치	  : 뭔 행동이야 이건.....(아직까진 정의되지 않은 행동으로 생각.)
			// begin과 end사이 		: position부터 end까지 한 칸씩 뒤로 밀고, position에 val를 넣는다.
			// end보다 크다		 	 : capacity를 넘어가면 capacity * 2만큼 재할당 해주고 position에 val를 넣는다.
			//						 근데 재할당해준 capacity의 범위를 넘어가도 position에 val를 넣어줌...?(정의되지 않은 행동으로 생각.)
			// max_size보다 크다	 : begin에 val를 넣어주고 한 칸씩 뒤로 민다.
		iterator	insert(iterator position, const value_type& val)
		{
			size_type	curr_cap = 0;
			if (size() == capacity())
				curr_cap = 2 * capacity();
			else if (capacity() == 0)
				curr_cap = 1;
			else
				curr_cap = capacity();
			pointer		change_begin = _alloc.allocate(curr_cap);
			pointer		change_end = change_begin;
			pointer		change_end_cap = change_begin + curr_cap;
			pointer		start = _begin;
			while (size() != 0 && start != &(*position))
				_alloc.construct(change_end++, *start++);
			pointer		res = change_end;
			_alloc.construct(change_end++, val);
			while (size() != 0 && start != _end)
				_alloc.construct(change_end++, *start++);
			this->clear();
			_alloc.deallocate(_begin, capacity());
			_begin = change_begin;
			_end = change_end;
			_end_cap = change_end_cap;
			return (iterator(res));
		};
		void	insert(iterator position, size_type n, const value_type& val)
		{
			if (0 < n && n < max_size())
			{
				size_type	curr_cap = 0;
				if (capacity() <= n)
				{
					if (size() + n >= 2 * capacity())
						curr_cap = size() + n;
					else
						curr_cap = 2 * capacity();
				}
				else if (capacity() == 0)
					curr_cap = n;
				else	// (capacity() > n)
				{
					if (n + size() <= capacity())
						curr_cap = capacity();
					else
						curr_cap = 2 * capacity();
				}
				pointer	change_begin = _alloc.allocate(curr_cap);
				pointer	change_end = change_begin;
				pointer	change_end_cap = change_begin + curr_cap;
				pointer	start = _begin;
				pointer	stop = &(*position);

				while (size() != 0 && start != stop)
					_alloc.construct(change_end++, *start++);
				for (size_type i = 0; i < n; i++)
					_alloc.construct(change_end++, val);
				while (size() != 0 && start != _end)
					_alloc.construct(change_end++, *start++);
				this->clear();
				_alloc.deallocate(_begin, capacity());
				_begin = change_begin;
				_end = change_end;
				_end_cap = change_end_cap;
			}
		}
		template <class InputIter>
		void insert (iterator position, InputIter first, InputIter last
					, typename ft::enable_if<!ft::is_integral<InputIter>::value_type, InputIter>::type* = m_nullptr)
		{
			size_type	n = &(*last) - &(*first);
			if (0 < n && n < max_size())
			{
				size_type	curr_cap = 0;
				if (capacity() <= n)
				{
					if (size() + n >= 2 * capacity())
						curr_cap = size() + n;
					else
						curr_cap = 2 * capacity();
				}
				else if (capacity() == 0)
					curr_cap = n;
				else	// (capacity() > n)
				{
					if (n + size() <= capacity())
						curr_cap = capacity();
					else
						curr_cap = 2 * capacity();
				}
				pointer	change_begin = _alloc.allocate(curr_cap);
				pointer	change_end = change_begin;
				pointer	change_end_cap = change_begin + curr_cap;
				pointer	start = this->_begin;
				pointer	stop = &(*position);

				while (size() != 0 && start != stop)
					_alloc.construct(change_end++, *start++);
				while (first != last)
					_alloc.construct(change_end++, *first++);
				while (size() != 0 && start != this->_end)
					_alloc.construct(change_end++, *start++);
				this->clear();
				_alloc.deallocate(this->_begin, this->capacity());
				this->_begin = change_begin;
				this->_end = change_end;
				this->_end_cap = change_end_cap;
			}
		}

		iterator erase (iterator position)
		{
			size_type	res_size = position - begin();
			pointer		pos = &(*position);
			_alloc.destroy(pos);
			for (pointer i = _begin + res_size; i != _end; i++)
			{
				_alloc.construct(i, *(i + 1));
				_alloc.destroy(i + 1);
			}
			_end -= 1;
			return (iterator(_begin + res_size));
		}
		iterator erase (iterator first, iterator last)
		{
			size_type	res_size = first - begin();
			size_type	n = &(*last) - &(*first);

			for (; first != last; first++)
				_alloc.destroy(&(*first));
			for (pointer i = _begin + res_size; i != _end - n; i++)
			{
				_alloc.construct(i, *(i + n));
				_alloc.destroy(i + n);
			}
			_end -= n;
			return (iterator(_begin + res_size));
		}

		// private:
		// void	_swap(pointer &a, pointer &b)
		// {
		// 	pointer	temp = a;
		// 	a = b;
		// 	b = temp;
		// }

		// public:
		void	swap(vector& x)
		{
			if (this == &x)
				return ;
			pointer			temp_begin = x._begin;
			x._begin = this->_begin;
			this->_begin = temp_begin;
			pointer			temp_end = x._end;
			x._end = this->_end;
			this->_end = temp_end;
			pointer			temp_end_cap = x._end_cap;
			x._end_cap = this->_end_cap;
			this->_end_cap = temp_end_cap;
			// this->_swap(this->_begin, x._begin);
			// this->_swap(this->_end, x._end);
			// this->_swap(this->_end_cap, x._end_cap);
			allocator_type	temp_alloc = x._alloc;
			x._alloc = this->_alloc;
			this->_alloc = temp_alloc;
		}

		void	clear()
		{
			while (_end != _begin)
				_alloc.destroy(--_end);
		}

		// Allocator
		allocator_type	get_allocator() const { return (_alloc); };
	};
	// Non-member function overloading
		// Relational Operators
	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
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
	{ x.swap(y); }
}


#endif
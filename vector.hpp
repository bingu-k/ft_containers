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
		typedef ft::reverse_iterator<T>						reverse_iterator;
		typedef ft::reverse_iterator<const T>				const_reverse_iterator;
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
			{
				_alloc.construct(_end, val);
				_end++;
			}
		};

		// 위의 생성자와 구분하기 위해서 is_intergral을 사용하여 정수 자료형을 제외한다.(SFINAE)
		// iterator의 종류를 구분하여 되는 것과 안되는것을 구분하자.
		// 원본 함수를 보면 is_convertible을 사용하여 변환의 문제로 true or false로 확인한다.
		// 그럼 여기서 상속 구조를 보면 input <- forward <- bidirection <- random access
		// output은 따로 떨어져있다.
		// vector의 iterator는 random access iterator로 output iterator이외는 전부 변환 가능하다.
		template <class InputIter>
		vector (InputIter first, InputIter last, const allocator_type& alloc = allocator_type()
				, typename ft::enable_if<!ft::is_integral<InputIter>::value_type, InputIter>::type isIter = InputIter())
		: _alloc(alloc), _begin(0), _end(0), _end_cap(0)
		{
			difference_type	n = ft::distance(first, last);
			_begin = _alloc.allocate(n);
			_end = _begin;
			_end_cap = _begin + n;
			while (first != last)
			{
				_alloc.construct(_end, *first);
				_end++;
				first++;
			}
			_alloc.construct(_end++, *first);
		};

		vector (const vector& x)
		: _alloc(x._alloc), _begin(0), _end(0), _end_cap(0)
		{
			_begin = _alloc.allocate(x.capacity());
			this->insert(_begin, x.begin(), x.end());
		};

		// vector (vector& x)

		~vector()
		{
			if (this->capacity != 0)
			{
				this->clear();
				this->_alloc.deallocate(this->_begin, this->capacity());
			}
		};

		// Operator overloading
		vector	&operator=(const vector& x)
		{
			if (this != &x)
			{
				_begin = _alloc.allocate(x.capacity());
				this->insert(_begin, x.begin(), x.end());
			}
			return (*this);
		}
		// vector	&operator=(vector& x)
		

		// Iterators
		iterator		begin() { return (_begin); };
		const_iterator	begin() const { return (_begin); };
		iterator		end() { return (_end); };
		const_iterator	end() const { return (_end); };
		// reverse_iterator		rbegin() { return (); };
		// const_reverse_iterator	rbegin() const { return (); };
		// reverse_iterator		rend() { return (); };
		// const_reverse_iterator	rend() const { return (); };

		// Capacity
		size_type		size(void) const { return (static_cast<size_type>(_end - _begin);); };
		size_type		max_size(void) const { return (_alloc.max_size();); };

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
			else if (n > size())
			{
				size_type	_size = (size() * 2 < n ? n : size());
				pointer		change_begin = _alloc.allocate(_size);
				pointer		change_end = change_begin;
				size_type	prev_size = size();

				while (_begin != _end)
				{
					_alloc.construct(change_end++, *_begin);
					_begin++;
				}
				while (prev_size++ != n)
					_alloc.construct(change_end++, val);
				this->clear();
				_alloc.deallocate(_begin, capacity());
				_begin = change_begin;
				_end = change_end;
				_end_cap = change_begin + _size;
			}
			else if (n < size())
			{
				pointer	remove_container = _begin + n;

				while (remove_container != _end)
					_alloc.destroy(remove_container++);
				_end = _begin + n;
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
				pointer		prev_begin = _begin;
				pointer		prev_end = _end;
				size_type	prev_size = size();
				size_type	prev_cap = capacity();

				_begin = _alloc.allocate(n);
				_end = _begin;
				_end_cap = _begin + n;
				while (prev_begin != prev_end)
				{
					_alloc.construct(_end++, *prev_begin);
					prev_begin++;
				}
				_alloc.deallocate(prev_begin - prev_size, prev_cap);
			}
		}

		// Element access
		reference		operator[] (size_type n) { return (*(_begin + n)); };
		const_reference	operator[] (size_type n) const { return (*(_begin + n)); };

		reference		at(size_type n)
		{
			if (n > size())
				throw(std::out_of_range("vector"));
			return (*(begin + n));
		};
		const_reference	at(size_type n) const
		{
			if (n > size())
				throw(std::out_of_range("vector"));
			return (*(begin + n));
		};

		reference		front(void) { return (*_begin); };
		const_reference	front(void) const { return (*_begin); };
		reference		back(void) { return (*_end); };
		const_reference	back(void) const { return (*_end); };

		// Modifiers
		template <class InputIterator>
		void	assign(InputIterator first, InputIterator last
						, typename ft::enable_if<!ft::is_integral<InputIter>, InputIter>::type isIter = InputIter())
		{
			size_type	n = static_cast<size_type>(ft::distance(first, last));
			pointer		prev_iter = _begin;
			pointer		prev_cap = capacity();

			while (prev_iter != _end)
				_alloc.destroy(prev_iter++);
			if (capacity() < n)
			{
				_alloc.deallocate(_begin, capacity());
				_begin = _alloc.allocate(n);
				_end_cap = _begin;
			}
			_end = _begin;
			while (first != last)
			{
				_alloc.construct(_end++, *first);
				first++;
			}
		};
		void	assign(size_type n, const value_type& val)
		{
			if (n < 0 || n > max_size())
				throw(std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size"));
			else
			{
				pointer	prev_begin = _begin;
				pointer	prev_end = _end;
				pointer	prev_size = size();
				pointer	prev_cap = capacity();


				while (prev_begin != prev_end)
					_alloc.destroy(prev_begin++);
				if (prev_cap < n)
				{
					_alloc.deallocate(_begin, prev_cap);
					_begin = _alloc.allocate(n);
					_end_cap = _begin + n;
				}
				_end = _begin;
				for (int i = 0; i < n; i++)
					_alloc.construct(_end++, val);
			}
		};

		// 초기값은 0, 추가되면 1, 계속 추가되면 2의 지수승으로 커진다.
		void	push_back(const value_type& val)
		{
			if (size() == capacity())
				resize(size() * 2);
			_alloc.construct(_end++, val);
		};

		void pop_back(void) { _alloc.destroy(_end--) };

		// 동작 : 해당 위치에 val을 추가한다. capacity를 넘어갈 경우 재할당.
		// 예외(position)
			// begin보다 작은 위치	  : 뭔 행동이야 이건.....(아직까진 정의되지 않은 행동으로 생각.)
			// begin과 end사이 		: position부터 end까지 한 칸씩 뒤로 밀고, position에 val를 넣는다.
			// end보다 크다		 	 : capacity를 넘어가면 capacity * 2만큼 재할당 해주고 position에 val를 넣는다.
			//						 근데 재할당해준 capacity의 범위를 넘어가도 position에 val를 넣어줌...?(정의되지 않은 행동으로 생각.)
			// max_size보다 크다	 : begin에 val를 넣어주고 한 칸씩 뒤로 민다.
		iterator	insert(iterator position, const value_type& val);
		{
			pointer	pos = &(*position);
			if (size() == capacity())				// 재할당 해야할 때.
				resize(capacity() * 2);
			if (position - begin() > max_size())	// max_size보다 클 때.
				pos = _begin;
			pointer	mid_pos = _end;
			int		tmp		= 0;
			while (mid_pos != pos)
			{
				tmp = *(mid_pos - 1);
				_alloc.destroy(mid_pos - 1);
				_alloc.construct(mid_pos--, tmp);
			}
			_end = _end + 1;
			_alloc.construct(pos, val);
			return (pos);
		}
		void insert (iterator position, size_type n, const value_type& val)
		{
			pointer	pos = &(*position);
			if (size() + n > capacity())			// 재할당 해야할 때.
				resize(capacity() * 2);
			if (position - begin() > max_size())	// max_size보다 클 때.
				pos = _begin;
			pointer	mid_pos = _end;
			int		tmp		= 0;
			while (mid_pos != pos)
			{
				tmp = *(mid_pos - n);
				_alloc.destroy(mid_pos - n);
				_alloc.construct(mid_pos--, tmp);
			}
			_end = _end + n;
			for (int i = 0; i < n; i++)
				_alloc.construct(pos++, val);
		}
		template <class InputIter>
		void insert (iterator position, InputIter first, InputIter last
					, typename ft::enable_if<!ft::is_integral<InputIter>, InputIter>::type isIter = InputIter())
		{
			size_type	n = last - first;
			pointer		pos = &(*position);
			if (size() + n > capacity())
				resize(capacity() * 2);
			if (position - begin() > max_size())
				pos = _begin;
			if (size() != 0)
			{
				pointer	mid_pos = _end;
				int		tmp = 0;
				while (mid_pos != pos)
				{
					tmp = *(mid_pos - n);
					_alloc.destroy(mid_pos - n);
					_alloc.construct(mid_pos--, tmp);
				}
				_end = _end + n;
			}
			while (first != last)
			{
				_alloc.construct(pos++, *first);
				first++;
			}
		}

		iterator erase (iterator position)
		{
			pointer	move_element = position + 1;

			while (move_element != _end)
			{
				_alloc.destroy(move_element - 1);
				_alloc.construct(move_element - 1, move_element);
			}
			_end = move_element - 1;
			return (position);
		}
		iterator erase (iterator first, iterator last);
		{
			size_type	n = last - first;
			pointer		move_element = position + n;

			while (move_element != _end)
			{
				_alloc.destroy(move_element - n);
				_alloc.construct(move_element - n, move_element);
			}
			_end = move_element - n;
			return (position);
		}

	private:
		void	swap(pointer a, pointer b)
		{
			pointer	tmp = a;
			a = b;
			b = tmp;
		}

	public:
		void	swap(vector& x)
		{
			swap(_begin, x._begin);
			swap(_end, x._end);
			swap(_end_cap, x._end_cap);
		}

		void	clear()
		{
			pointer	remove_container = _begin + 1;

			while (remove_container != _end)
				_alloc.destroy(remove_container - 1);
			_begin = 0;
			_end = 0;
		}

		// Allocator
		allocator_type	get_allocator() const { return (_alloc); };
	};
	// Non-member function overloading
		// Relational Operators
	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		typename ft::vector_iterator<T>	lhs_container = lhs.begin();
		typename ft::vector_iterator<T>	rhs_container = rhs.begin();

		while (lhs_container != lhs.end())			// lhs 끝까지 돌리고
		{
			if (rhs_container == rhs.end())			// rhs가 끝에 도달하면 false 
				return (false);
			else if (lhs_container++ != rhs_container++)	// lhs와 rhs가 다르면 false
				return (false);
		}
		if (rhs_container == rhs.end())				// lhs와 rhs가 끝까지 갔다면 true
			return (true);
		return (false);								// lhs는 끝까지 갔는데 rhs가 끝까지 못갔다면 false
	};

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{ return (!(lhs == rhs)); };

	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		typename ft::vector_iterator<T>	lhs_container = lhs.begin();
		typename ft::vector_iterator<T>	rhs_container = rhs.begin();

		while (lhs_container != lhs.end())			// lhs 끝까지 돌리고
		{
			if (rhs_container == rhs.end())			// rhs가 끝에 도달하면 false 
				return (false);
			if (lhs_container++ >= rhs_container++)	// lhs가 rhs보다 크거나 같으면 false
				return (false);
		}
		if (rhs_container == rhs.end())				// lhs와 rhs가 끝까지 갔다면 false
			return (false);
		return (true);								// lhs는 끝까지 갔는데 rhs가 끝까지 못갔다면 true
	};

	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{ return ((lhs < rhs) || (lhs == rhs)); };

	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{ return (!(lhs <= rhs)); };

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{ return (!(lhs < rhs)); };

	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{ x.swap(y); }
}


#endif
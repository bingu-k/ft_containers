#ifndef	VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include "vector_iterator.hpp"

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
		// reverse_iterator
		// const_reverse_iterator
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
				, typename ft::enable_if<!ft::is_integral<InputIter>, InputIter>::type isIter = InputIter())
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
			difference_type						cap = x.capacity();
			difference_type						size = x.size();
			ft::vector<value_type>::iterator	temp = x.begin();

			_begin = _alloc.allocate(cap);
			_end = _begin;
			_end_cap = _begin + cap;
			while (size < 0)
			{
				_alloc.construct(_end, *temp);
				_end++;
				temp++;
			}
			_alloc.construct(_end++, *temp);
		};

		// vector (vector& x)

		~vector()
		{
			if (this->capacity != 0)
			{
				this->clear();
				this->_alloc.deallocate(this->_begin, this->capacity);
			}
		};

		// Operator overloading
		vector	&operator=(const vector& x)
		{
			if (this != &x)
			{
				if (this->capacity != 0)
				{
					this->clear();
					this->_alloc.deallocate(this->_begin, this->capacity);
				}
				difference_type						cap = x.capacity();
				difference_type						size = x.size();
				ft::vector<value_type>::iterator	temp = x.begin();
				_begin = _alloc.allocate(cap);
				_end = _begin;
				_end_cap = _begin + cap;
				while (size < 0)
				{
					_alloc.construct(_end, *temp);
					_end++;
					temp++;
				}
				_alloc.construct(_end++, *temp);
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
		// 2의 지수승으로 커진다.
		// 원래의 size보다 n이 클때,
			// val이 없으면 원래 존재하는 컨테이너 이후부터 0으로 채운다.
			// val이 있으면 원래 존재하는 컨테이너 이후부터 val으로 채운다.
		// 원래의 size보다 n이 작을때,
			// size가 n으로 될 수 있게 destroy해주고 end를 옮겨준다.
		void			resize (size_type n, value_type val = value_type())
		{
			if (n < 0 || n > max_size())
				throw(std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size"));
			else if (n < size())
			{}
			
		};
		size_type		capacity(void) const { return (_end_cap - _begin); };
		bool			empty(void) const { return (_begin == _end); };
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
					_alloc.construct(_end, *prev_begin);
					_end++;
					prev_begin++;
				}
				_alloc.deallocate(prev_begin - prev_size, prev_cap);
			}
		}

		// Element access
		reference		operator[] (size_type n) { return (*(_begin + n)); };
		const_reference	operator[] (size_type n) const { return (*(_begin + n)); };
		reference		at (size_type n)
		{
			if (n > size())
				throw(std::out_of_range("vector"));
			return (*(begin + n));
		};
		const_reference	at (size_type n) const
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
		void assign		(InputIterator first, InputIterator last
						, typename ft::enable_if<!ft::is_integral<InputIter>, InputIter>::type isIter = InputIter())
		{
			size_type	n = static_cast<size_type>(ft::distance(first, end));
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
		void assign		(size_type n, const value_type& val)
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
		// void push_back (const value_type& val);
		// 초기값은 0, 추가되면 1, 계속 추가되면 2의 지수승으로 커진다.
		// void pop_back();
		// iterator insert (iterator position, const value_type& val);
		// void insert (iterator position, size_type n, const value_type& val);
		// template <class InputIterator>
		// void insert (iterator position, InputIterator first, InputIterator last);
		// iterator erase (iterator position);
		// iterator erase (iterator first, iterator last);
		// void swap (vector& x);
		// void clear();

		// Allocator
		allocator_type	get_allocator() const { return (_alloc); };
	};
	// Non-member function overloading
		// Relational Operators
	// template <class T, class Alloc>
	// bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	// template <class T, class Alloc>
	// bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	// template <class T, class Alloc>
	// bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	// template <class T, class Alloc>
	// bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	// template <class T, class Alloc>
	// bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	// template <class T, class Alloc>
	// bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	// template <class T, class Alloc>
	// void swap (vector<T,Alloc>& x, vector<T,Alloc>& y);
}


#endif
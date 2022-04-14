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
			if (ft::is_iter_tag(typename ft::iterator_traits<InputIter>::iterator_category)::value)
				throw (ft::invalid_iter());
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
		// size_type size() const;
		// size_type max_size() const;
		// void resize (size_type n, value_type val = value_type());
		// size_type capacity() const;
		// bool empty() const;
		// void reserve (size_type n);

		// Element access
		// reference operator[] (size_type n);
		// const_reference operator[] (size_type n) const;
		// reference at (size_type n);
		// const_reference at (size_type n) const;
		// reference front();
		// const_reference front() const;
		// reference back();
		// const_reference back() const;

		// Modifiers
		// template <class InputIterator>
		// void assign (InputIterator first, InputIterator last);
		// void assign (size_type n, const value_type& val);
		// void push_back (const value_type& val);
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
		// allocator_type get_allocator() const;
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
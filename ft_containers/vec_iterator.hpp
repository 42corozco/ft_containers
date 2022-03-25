#ifndef VEC_ITERATOR_HPP
# define VEC_ITERATOR_HPP

#include "iterator.hpp"
#include "iterator_traits.hpp"
#include <iostream>

/*sources
	https://www.cplusplus.com/reference/iterator/RandomAccessIterator/
	https://codereview.stackexchange.com/questions/202157/basic-iterator-supporting-vector-implementation
	https://lokiastari.com/series/

	friend operators (bool) https://stackoverflow.com/questions/3850058/friend-in-operator-or-when-should-i-use-it
*/

namespace	ft
{
	template <class T>
	class vec_iterator : ft::iterator< std::random_access_iterator_tag, T>
	{
		public:
		typedef typename	ft::iterator<std::random_access_iterator_tag, T>::value_type value_type;
		typedef typename	ft::iterator<std::random_access_iterator_tag, T>::difference_type	difference_type;
		typedef typename	ft::iterator<std::random_access_iterator_tag, T>::pointer	pointer;
		typedef typename	ft::iterator<std::random_access_iterator_tag, T>::reference	reference;
		typedef typename	ft::iterator<std::random_access_iterator_tag, T>::iterator_category	iterator_category;


		vec_iterator() { _ptr = NULL; }
		vec_iterator(T *p) { _ptr = p; }
		vec_iterator(const vec_iterator & cpy) { _ptr = cpy._ptr; }
		vec_iterator & operator= (const vec_iterator &cpy) { this->_ptr = cpy._ptr; return *this; }
				//	~vec_iterator(); // https://stackoverflow.com/questions/20677090/c-define-a-destructor-in-an-iterator-class
		operator vec_iterator<const value_type>() const { return (vec_iterator<const value_type>(_ptr)); }

		//operations * and -> 
		reference	operator* () const { return (*(this->_ptr)); }
		pointer		operator-> () const { return (this->_ptr); }

		//incremented
		vec_iterator & operator++ () { ++(this->_ptr); return (*this); }
		vec_iterator operator++ (int) { return (vec_iterator(this->_ptr++)); }

		//decremented
		vec_iterator & operator-- () { --(this->_ptr); return (*this); }
		vec_iterator operator-- (int)						{ return (vec_iterator(this->_ptr--)); }

		//the arithmetic operators + and -
		vec_iterator operator+ (difference_type a) const	{ return (vec_iterator(this->_ptr + a));}
		vec_iterator  operator- (difference_type a) const	{ return (vec_iterator(this->_ptr - a));}

		//operations += and -=
		vec_iterator & operator+= (difference_type a) { this->_ptr += a; return (*this); }
		vec_iterator & operator-= (difference_type a) { this->_ptr -= a; return (*this); }

		//dereference operator ([])
		reference	operator[] (size_t x) { return (*(this->_ptr + x)); }
		pointer		operator[] (size_t x) const { return (*(this->_ptr + x)); }

		// equality/inequality operators == and !=

		//https://stackoverflow.com/questions/3850058/friend-in-operator-or-when-should-i-use-it
/*
		template <class a1, class a2>
		friend	bool	operator == (const vec_iterator<a1> & c1, const vec_iterator<a2> & c2)	{ return (c1._ptr == c2._ptr); }

		template <class a1, class a2>
		friend	bool	operator != (const vec_iterator<a1> & c1, const vec_iterator<a2> & c2)	{ return (c1._ptr != c2._ptr); }

		// operators (<, >, <= and >=).
		template <class a1, class a2>
		friend	bool	operator <  (const vec_iterator<a1> & c1, const vec_iterator<a2> & c2)	{ return (c1._ptr < c2._ptr); }

		template <class a1, class a2>
		friend	bool	operator >  (const vec_iterator<a1> & c1, const vec_iterator<a2> & c2)	{ return (c1._ptr > c2._ptr); }

		template <class a1, class a2>
		friend	bool	operator <= (const vec_iterator<a1> & c1, const vec_iterator<a2> & c2)	{ return (c1._ptr <= c2._ptr); }

		template <class a1, class a2>
		friend	bool	operator >= (const vec_iterator<a1> & c1, const vec_iterator<a2> & c2)	{ return (c1._ptr >= c2._ptr); }

		template <class a1, class a2>
		friend difference_type	operator-(const vec_iterator<a1> & c1, const vec_iterator<a2> & c2) { return (c1._ptr - c2._ptr); }

		template <class a1>
		friend	vec_iterator	operator + (difference_type a, const vec_iterator<a1> &it) { return (vec_iterator(it + a)); }
*/
		private:
			T *		_ptr;

	};
};

#endif


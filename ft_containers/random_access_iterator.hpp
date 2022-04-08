#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include "iterator.hpp"
# include "iterator_traits.hpp"

namespace ft
{
	template <typename T>
	class	random_access_iterator : public iterator<ft::random_access_iterator_tag, T>
	{
		public:
		typedef T										value_type;
		typedef T&										reference;
		typedef T*										pointer;
		typedef const T&								const_reference;
		typedef const T*								const_pointer;
		typedef std::ptrdiff_t							difference_type;
		typedef std::size_t								size_type;
		typedef typename ft::random_access_iterator_tag	iterator_category;

			//****** default-constructible, copy-constructible, copy-assignable and destructible ******//
		random_access_iterator(){ this->_ptr = NULL; };
		random_access_iterator(T* ptr):_ptr(ptr){};
		random_access_iterator(random_access_iterator<T> const &cpy): _ptr(cpy._ptr) {}
//			virtual ~random_access_iterator(void){};	// https://stackoverflow.com/questions/20677090/c-define-a-destructor-in-an-iterator-class


		random_access_iterator &operator=(random_access_iterator<T> const &cpy)
		{
			if (this != &cpy)
				this->_ptr = cpy._ptr;
			return *this;
		}

		// si se intenta copiar un const_iterator basado en un iterador
		operator random_access_iterator<T const>() const{ return random_access_iterator<T const>(this->_ptr);}

		pointer	base(void) const { return this->_ptr; }

		// compared for equivalence == and !=
		bool operator==(const random_access_iterator &src) const	{ return this->_ptr == src._ptr; }
		bool operator!=(const random_access_iterator &src) const	{ return this->_ptr != src._ptr; }

			//operations * and -> (access)
		pointer			operator->()							{ return(this->_ptr); }
		reference		operator*() 							{ return (*_ptr); }
		reference	 	operator[](difference_type op) const	{ return(_ptr[op]); }

		//****** compared with inequality relational operators (<, >, <= and >=). ******//
		bool operator>(const random_access_iterator &src) const		{ return this->_ptr >  src._ptr; }
		bool operator>=(const random_access_iterator &src) const	{ return this->_ptr >= src._ptr; }
		bool operator<(const random_access_iterator &src) const		{ return this->_ptr <  src._ptr; }
		bool operator<=(const random_access_iterator &src) const	{ return this->_ptr <= src._ptr; }

		//relational operator between const and non const iterator
		// must be friend to access protected _ptr in non membre functions
		template <class I1, class I2>
		friend bool operator==(const random_access_iterator<I1> &o1,const random_access_iterator<I2> &o2);
		template <class I1, class I2>
		friend bool operator!=(const random_access_iterator<I1> &o1,const random_access_iterator<I2> &o2);
		template <class I1, class I2>
		friend bool operator>(const random_access_iterator<I1> &o1,const random_access_iterator<I2> &o2);
		template <class I1, class I2>
		friend bool operator>=(const random_access_iterator<I1> &o1,const random_access_iterator<I2> &o2);
		template <class I1, class I2>
		friend bool operator<(const random_access_iterator<I1> &o1,const random_access_iterator<I2> &o2);
		template <class I1, class I2>
		friend bool operator<=(const random_access_iterator<I1> &o1,const random_access_iterator<I2> &o2);

			//incremented
			//random_access_iterator	operator--(int){ random_access_iterator old = *this; _ptr--; return(old); }
		random_access_iterator	&operator++(){ this->_ptr++; return(*this); }
		random_access_iterator	operator++(int) { return (random_access_iterator(this->_ptr++)); }
		//decremented
		random_access_iterator	&operator--(){ this->_ptr--; return(*this); }
		random_access_iterator	operator--(int) { return (random_access_iterator(this->_ptr--)); }


		//the arithmetic operators + and -
		//random_access_iterator	operator-(difference_type a)const{return(random_access_iterator<T>(_ptr - op));};
		random_access_iterator	operator+(difference_type a)const { return (random_access_iterator<T>(this->_ptr + a));}
		random_access_iterator	operator-(difference_type a)const { return (random_access_iterator<T>(this->_ptr - a));}
		difference_type			operator-(random_access_iterator const &src) const {return this->_ptr - src._ptr;}

		//+= -= operators
		random_access_iterator	&operator+=(difference_type op) {this->_ptr += op; return *this;}
		random_access_iterator	&operator-=(difference_type op) {this->_ptr -= op; return *this;}


		private:
		T*	_ptr;

	};

	template <class T>
	ft::random_access_iterator<T> operator+(typename ft::random_access_iterator<T>::difference_type n, ft::random_access_iterator<T> const & o2) { return o2 + n; };

	template <typename T, typename U>
	ptrdiff_t	operator-(const random_access_iterator<T> &o1, const random_access_iterator<U> &o2) { return (o1.base() - o2.base()); }

	template <typename I1, typename I2>
	bool operator==(const random_access_iterator<I1> &o1, const random_access_iterator<I2> &o2) { return (o1._ptr == o2._ptr); }

	template <typename I1, typename I2>
	bool operator!=(const random_access_iterator<I1> &o1, const random_access_iterator<I2> &o2) { return (o1._ptr != o2._ptr); }

	template <typename I1, typename I2>
	bool operator<(const random_access_iterator<I1> &o1, const random_access_iterator<I2> &o2) { return (o1._ptr < o2._ptr); }

	template <typename I1, typename I2>
	bool operator>(const random_access_iterator<I1> &o1, const random_access_iterator<I2> &o2) { return (o1._ptr > o2._ptr); }

	template <typename I1, typename I2>
	bool operator>=(const random_access_iterator<I1> &o1, const random_access_iterator<I2> &o2) { return (o1._ptr >= o2._ptr); }

	template <typename I1, typename I2>
	bool operator<=(const random_access_iterator<I1> &o1, const random_access_iterator<I2> &o2) { return (o1._ptr <= o2._ptr); }
}

#endif

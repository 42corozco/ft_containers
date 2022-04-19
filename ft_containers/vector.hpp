#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>

# include <sstream> //stringstream

# include "random_access_iterator.hpp"
# include "reverse_iterator.hpp"
# include "utils.hpp"
# include "is_integral.hpp"

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
		typedef T				value_type;
		typedef  Allocator		allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef ptrdiff_t	difference_type;
		typedef size_t		size_type;

		typedef typename ft::random_access_iterator<T>			iterator;
		typedef typename ft::random_access_iterator<const T>	const_iterator;

		typedef typename ft::reverse_iterator<iterator>				reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>		const_reverse_iterator;


		/**********MEMBER FUNCTIONS**********/
		//default (1)
		explicit vector (const allocator_type& alloc = allocator_type())
		{
			this->tmp = alloc;
			this->_tab = 0;
			this->_size = 0;
			this->_capacity = 0;
		}
		// fill (2)	
		explicit vector (size_type n, const value_type& val = value_type(),
			const allocator_type& alloc = allocator_type())
		: tmp(alloc), _size(n), _capacity(n)
		{
			this->_tab = this->tmp.allocate(n);
			for (unsigned int i = 0; i < n; i++)
			{
				tmp.construct(&_tab[i], val);
				//this->_tab[i] = val;
			}
		};
		// range (3)
		//	->	https://stackoverflow.com/questions/28529376/stdvector-constructor-taking-pair-of-iterators
		//	->	https://h-deb.clg.qc.ca/Sujets/TrucsScouts/Comprendre_enable_if.html
		
		template<class InputIt>
		vector(InputIt first, InputIt last, const Allocator& alloc = Allocator(),
		typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL)
		: _tab(0), tmp(alloc), _size(0), _capacity(0)
		{
			while (first != last)
			{
				this->push_back(*first);
				first++;
			}
		};

		// copy (4)
		vector (vector<T, Allocator> const & x)
			: _tab(0), tmp(x.tmp), _size(0), _capacity(0)
		{
			*this = x;
		};

		~vector()
		{
			if (this->_tab)
			{
				clear();
				if (this->_capacity)
					this->tmp.deallocate(this->_tab, this->_capacity);
			}
		}

		vector& operator= (const vector& obj)
		{
			if (this->_tab)
				clear();

			if (obj.size() > this->_capacity)
			{
				this->tmp.deallocate(this->_tab, this->_capacity);
				this->_tab = tmp.allocate(obj.size());
				this->_capacity = obj.size();
			}

			for (unsigned int i = 0; i < obj._size ;i++)
				push_back(obj[i]);

			return (*this);
		}

		/**********ITERATORS**********/
		iterator begin() { return(iterator(this->_tab)); }
		const_iterator begin() const { return(const_iterator(this->_tab)); }
		iterator end() { return(iterator(this->_tab + this->_size)); }
		const_iterator end() const { return(const_iterator(this->_tab + this->_size)); }
		reverse_iterator rbegin() { return(reverse_iterator(this->_tab + this->_size)); }
		const_reverse_iterator rbegin() const { return(const_reverse_iterator(this->_tab + this->_size)); }
		reverse_iterator rend() { return(reverse_iterator(this->_tab)); }
		const_reverse_iterator rend() const { return(const_reverse_iterator(this->_tab)); }

		/**********CAPACITY**********/
		size_type	size() const { return (_size); };
		size_type	max_size() const { return (size_t(-1) / sizeof(T)); }
		void resize (size_type n, value_type val = value_type())
		{
			value_type	*newtab;                               //meter assing(2)(punteros) que servira /-

			unsigned int	osize = this->_size;
				if (this->_capacity < n)									//n
				this->_capacity = n;									//n
			this->_size = n;											//n
				newtab = this->tmp.allocate(this->_capacity);				//n
			for (unsigned int i = 0; i < this->_size; i++)				//n
				newtab[i] = val;										//n
			for (unsigned int i = 0; i < osize && i < this->_capacity; i++)
				newtab[i] = this->_tab[i];
			for (unsigned int i = 0; i < osize && i < this->_size; i++)
				tmp.destroy(&_tab[i]);
			this->tmp.deallocate(this->_tab, this->_capacity);				//n
			this->_tab = newtab;										//n
		}
		size_type	capacity() const { return (_capacity); }
		bool empty() const { return (_size == 0); }
		void reserve (size_type n)
		{
			value_type	*newtab;

			if (n <= this->_capacity)
				return ;
			newtab = this->tmp.allocate(n);
			for (unsigned int i = 0; i < this->_size; i++)
			{
				tmp.construct(&newtab[i], this->_tab[i]);
			}
			for (unsigned int i = 0; i < this->_size; i++)
			{
				this->tmp.destroy(&this->_tab[i]);
			}
			this->tmp.deallocate(this->_tab, this->_capacity);
			this->_tab = newtab;
			this->_capacity = n;
		}

		/**********ELEMENT ACCESS**********/
		reference operator[] (size_type n) { return (_tab[n]); }
		const_reference operator[] (size_type n) const { return (_tab[n]); }
		reference at (size_type n)
		{
			if (n >= _size)
				throw _voor(n);
			return (_tab[n]);
		}
		const_reference at (size_type n) const
		{
			if (n >= _size)
				throw _voor(n);
			return (_tab[n]);
		}
		reference front() { return (*this->_tab); }
		const_reference front() const { return (*this->_tab); }
		reference back() { return (*(this->_tab + this->_size - 1)); }
		const_reference back() const { return (*(this->_tab + this->_size - 1)); }

		/**********MODIFIERS**********/
		template<class InputIterator>
		void	assign(InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last)
		{
			if (size() != 0)
				clear();
			for (; first != last; first++)
					push_back(*first);
		}

		void assign (size_type n, const value_type& val)
		{
			if (size() != 0)
				clear();
			while (size() < n)
				push_back(val);
		/*
			if (n <= this->_capacity)
			{
				this->_size = n;
				for (unsigned int i = 0; i < this->_size ; i++)
					this->_tab[i] = val;
			}
			else
			{
				value_type	*newtab;

				for (unsigned int i = 0; i < this->_size ; i++)
					this->tmp.destroy(&this->_tab[i]);
				this->tmp.deallocate(this->_tab, this->_capacity);
				this->_capacity = n;
				this->_size = n;
				newtab = this->tmp.allocate(this->_capacity);
				for (unsigned int i = 0; i < this->_size; i++)
					newtab[i] = val;
				this->_tab = newtab;
			}
		*/
}

		void push_back (const value_type& val)
		{
			if (!this->_capacity)
			{
				this->tmp.deallocate(this->_tab, 0);
				this->_tab = this->tmp.allocate(1);
				this->_capacity++;
			}
			if (this->_size == this->_capacity)
				reserve(this->_capacity * 2);
			tmp.construct(&this->_tab[this->_size], val);
			this->_size++;
		}

		void pop_back()
		{
			if (this->_size > 0)
			{
				this->_size--;
				this->tmp.destroy(this->_tab + this->_size);
			}
		}

		iterator insert (iterator position, const value_type& val)
		{
			difference_type index = position - begin();
			insert(position, 1, val);
			return begin() + index;
		}

		void insert (iterator position, size_type n, const value_type& val)
		{
			difference_type		int_pos = position - this->begin();

			if (_capacity - _size < n)
				reserve(n);

			vector		temp(this->begin() + int_pos, this->end());

			for (size_t i = 0; i < temp.size(); i++)
				this->pop_back();
			while (n > 0)
			{
				this->push_back(val);
				n--;
			}
			for (iterator it = temp.begin(); it != temp.end(); it++)
				this->push_back(*it);
		}

		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = NULL)
		{
			size_t				count = 0;
			difference_type		int_pos = position - this->begin();

			while (first != last)
			{
				first++;
				count++;
			}
			first -= count;

			if (this->_capacity - this->_size < count)
				reserve(count);

			vector		temp(this->begin() + int_pos, this->end());

			for (size_t i = 0; i < temp.size(); i++)
				this->pop_back();
			while (first != last)
			{
				this->push_back(*first);
				first++;
			}
			for (iterator it = temp.begin(); it != temp.end(); it++)
				this->push_back(*it);
		}


		iterator erase (iterator position)
		{
			vector	tmp(position + 1, this->end());

			for (size_t i = 0; i < tmp.size(); i++)
				this->pop_back();
			this->pop_back();
			for (iterator it = tmp.begin(); it != tmp.end(); it++)
				this->push_back(*it);
			return (position);
		};

		iterator erase (iterator first, iterator last)
		{
			iterator tmp(first);

			while (tmp != last)
			{
				erase(first);
				tmp++;
			}
			return (first);
		}

		void swap (vector& x)
		{
			T * tmp_tab = x._tab;
			allocator_type tmp_tmp = x.tmp;
			size_type tmp_size = x._size;
			size_type tmp_capacity = x._capacity;
			
			x._tab = this->_tab;
			x.tmp = this->tmp;
			x._size = this->_size;
			x._capacity = this->_capacity;
			this->_tab = tmp_tab;
			this->tmp = tmp_tmp;
			this->_size = tmp_size;
			this->_capacity = tmp_capacity;
		}

		void clear()
		{
			//for (unsigned int i = 0 ; i < this->_size ; i++)
			for (int i = (int)this->_size-1 ; i >= 0 ; i--)
				this->tmp.destroy(&this->_tab[i]);
			this->_size = 0;
		}

		/**********ALLOCATOR**********/
		allocator_type	get_allocator() const { return (tmp); }
		protected:

		private:
		T * _tab;
		allocator_type tmp;
		size_type	_size;
		size_type	_capacity;

		std::out_of_range	_voor(size_type index) const
		{
			std::stringstream o;
			o << "vector::_M_range_check: __n (which is " << index << ")" \
			<< " >= this->size() (which is " << this->_size << ")";
			return (std::out_of_range(o.str()));
		};
	};

	/**********Non-member functions**********/
	//	->	https://www.cplusplus.com/reference/vector/vector/operators/

	template <class T, class Alloc>
	bool operator==(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc> &rhs) {
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool operator!=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc> &rhs) { return (!(lhs == rhs)); }

	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { return (!(rhs < lhs)); }

	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { return (rhs < lhs); }

	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { return (!(lhs < rhs)); }

	template <class T, class Alloc>
	void swap(vector<T, Alloc> &x, vector<T, Alloc> &y) { x.swap(y); }

};

#endif

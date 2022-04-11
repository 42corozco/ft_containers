#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>

# include <sstream> //stringstream

# include "random_access_iterator.hpp"
# include "reverse_iterator.hpp"

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

		typedef typename ft::reverse_iterator<T>				reverse_iterator;
		typedef typename ft::reverse_iterator<const T>			const_reverse_iterator;


		/**********MEMBER FUNCTIONS**********/
		explicit vector (const allocator_type& alloc = allocator_type())
		{
			this->tmp = alloc;
			this->_tab = this->tmp.allocate(0);
			this->_size = 0;
			this->_capacity = 0;
		}

		explicit vector (size_type n, const value_type& val = value_type(),
			const allocator_type& alloc = allocator_type())
		: tmp(alloc), _size(n), _capacity(n)
		{
			this->_tab = this->tmp.allocate(n);
			for (unsigned int i = 0; i < n; i++)
				this->_tab[i] = val;
		};

		//template <class InputIterator>
        //vector (InputIterator first, InputIterator last,
        //        const allocator_type& alloc = allocator_type());

		//vector (const vector& x);

		~vector()
		{
			//detroy?
			this->tmp.deallocate(this->_tab, this->_size);
		}

		vector& operator= (const vector& obj)
		{
			if (this->_tab)
				this->tmp.deallocate(this->_tab, this->_size);
			this->tmp = obj.tmp;
			this->_size = obj._size;
			this->_capacity = obj._capacity;
			this->_tab = this->tmp.allocate(this->_size);
			for (unsigned int i = 0; i < this->_size ;i++)
				this->_tab[i] = obj._tab[i];
			return (*this);
		}

		/**********ITERATORS**********/
			iterator begin() { return(iterator(this->_tab)); }
			const_iterator begin() const { return(const_iterator(this->_tab)); }
			iterator end() { return(iterator(this->_tab + this->_size)); }
			const_iterator end() const { return(const_iterator(this->_tab + this->_size)); }
//			reverse_iterator rbegin() { return(reverse_iterator(this->_tab + this->_size)); }
//			const_reverse_iterator rbegin() const { return(const_reverse_iterator(this->_tab + this->_size)); }
//			reverse_iterator rend() { return(reverse_iterator(this->_tab)); }
//			const_reverse_iterator rend() const { return(const_reverse_iterator(this->_tab)); }

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
			this->tmp.deallocate(this->_tab, this->_size);				//n
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
				newtab[i] = this->_tab[i];
			this->tmp.deallocate(this->_tab, this->_size);
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
		//template <class InputIterator>
			//void assign (InputIterator first, InputIterator last);

		void assign (size_type n, const value_type& val)
		{
			if (n <= this->_capacity)
			{
				this->_size = n;
				for (unsigned int i = 0; i < this->_size ; i++)
					this->_tab[i] = val;
			}
			else
			{
				value_type	*newtab;

				this->tmp.deallocate(this->_tab, this->_size);
				this->_capacity = n;
				this->_size = n;
				newtab = this->tmp.allocate(this->_capacity);
				for (unsigned int i = 0; i < this->_size; i++)
					newtab[i] = val;
				this->_tab = newtab;
			}
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
			this->_tab[this->_size] = val;
			this->_size++;
		}

		void pop_back()
		{
			if (this->_size > 0)
			{
				this->_size--;
				this->tmp.destroy(&this->_tab[this->_size]);
			}
		}

		//iterator insert (iterator position, const value_type& val);
		//void insert (iterator position, size_type n, const value_type& val);
		//template <class InputIterator>
			// void insert (iterator position, InputIterator first, InputIterator last);

		//iterator erase (iterator position);
		//iterator erase (iterator first, iterator last);

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
			for (unsigned int i = 0 ; i < this->_size ; i++)
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
};

#endif

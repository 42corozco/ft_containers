#ifndef BIDIRECTIONAL_ITERATOR_HPP
# define BIDIRECTIONAL_ITERATOR_HPP

# include "iterator.hpp"
# include "iterator_traits.hpp"
//# include "arbol.hpp"

namespace ft
{
	template <typename T, class N>
	class	bidirectional_iterator : public iterator<ft::bidirectional_iterator_tag, T>
	{
		public:
		typedef T										value_type;
		typedef T&										reference;
		typedef T*										pointer;
		typedef const T&								const_reference;
		typedef const T*								const_pointer;
		typedef std::ptrdiff_t							difference_type;
		typedef std::size_t								size_type;
		typedef typename ft::bidirectional_iterator_tag iterator_category;
		typedef N		_nodeType;
		typedef N*		_nodePtr;

		bidirectional_iterator()
		{
			this->_ptr = NULL;
			this->_root = NULL;
			this->_nill = NULL;
		}

		bidirectional_iterator(const bidirectional_iterator &cpy):_ptr(cpy._ptr), _root(cpy._root), _nill(cpy._nill) {}
		virtual ~bidirectional_iterator() {}

		bidirectional_iterator(_nodePtr ptr, _nodePtr root, _nodePtr nill):_ptr(ptr), _root(root), _nill(nill) {}

		operator	bidirectional_iterator<const value_type, const _nodeType>()const
		{
			return (bidirectional_iterator<const value_type, const _nodeType>(_ptr, _root, _nill));
		}
		
		bidirectional_iterator	&operator=(bidirectional_iterator const &cpy)
		{
			if (this !=&cpy)
			{
				this->_ptr = cpy._ptr;
				this->_root = cpy._root;
				this->_nill = cpy._nill;
			}
			return (*this);
		}

		//access
		reference		operator*()       { return (this->_ptr->data); }
		const_reference	operator*() const { return (this->_ptr->data); }

		pointer			operator->()       { return (&(this->_ptr->data)); }
		const_pointer	operator->() const { return (&(this->_ptr->data)); }

		//++
//		bidirectional_iterator		&operator++(void);
//		bidirectional_iterator		operator++(int);

		//--
//		bidirectional_iterator		&operator--(void);
//		bidirectional_iterator		operator--(int);


		//operator == et !=
		bool	operator==(const bidirectional_iterator &lhs) { return (this->_ptr == lhs.this->ptr); }
		bool	operator!=(const bidirectional_iterator &lhs) { return (this->_ptr != lhs.this->ptr); }

		private:
		_nodePtr	_ptr;
		_nodePtr	_root;
		_nodePtr	_nill;

	};
}

#endif
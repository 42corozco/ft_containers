#ifndef BIDIRECTIONAL_ITERATOR_HPP
# define BIDIRECTIONAL_ITERATOR_HPP

# include "iterator.hpp"
# include "iterator_traits.hpp"
# include "RedBlack.hpp"

namespace ft
{
    template <typename T, class N>
	class bidirectional_iterator : public iterator<ft::bidirectional_iterator_tag, T>
	{
		public:
		typedef T				value_type;
		typedef T&				reference;
		typedef T*				pointer;
		typedef const T&		const_reference;
		typedef const T*		const_pointer;
		typedef std::ptrdiff_t	difference_type;
		typedef std::size_t		size_type;
		typedef typename ft::bidirectional_iterator_tag	iterator_category;

		typedef N 				node_type;
		typedef N*				node_ptr;

		bidirectional_iterator()
		{
			this->_ptr = NULL;
			this->_root = NULL;
			this->_nill = NULL;
		}
		bidirectional_iterator(const bidirectional_iterator &cpy) :_ptr(cpy._ptr), _root(cpy._root), _nill(cpy._nill) {}

		bidirectional_iterator(node_ptr ptr, node_ptr root, node_ptr nill) : _ptr(ptr), _root(root), _nill(nill) {}

		/* para el const */
		operator bidirectional_iterator<const value_type, const node_type>()const
		{
			return (bidirectional_iterator<const value_type, const node_type>(_ptr, _root, _nill));
		}
		
		bidirectional_iterator &operator=(bidirectional_iterator const &cpy)
		{
			if (this != &cpy)
			{
				this->_ptr = cpy._ptr;
				this->_root = cpy._root;
				this->_nill = cpy._nill;
			}
			return (*this);
		}

		virtual ~bidirectional_iterator() {}

		//access
		reference		operator*()       { return (this->_ptr->data); }
		const_reference	operator*() const { return (this->_ptr->data); }

		pointer			operator->()       { return (&(this->_ptr->data)); }
		const_pointer	operator->() const { return (&(this->_ptr->data)); }

		//++
		bidirectional_iterator	&operator++()
		{
			if (this->_ptr != this->_nill)
				this->_ptr = successor(this->_ptr);
			return (*this);
		}

		bidirectional_iterator	operator++(int)
		{
			bidirectional_iterator	old(*this);
			this->operator++();
			return (old);
		}

		//--
		bidirectional_iterator  &operator--()
		{
			if (this->_ptr == this->_nill)
				this->_ptr = max(this->_root);
			else 
				this->_ptr = predecessor(this->_ptr);
			return (*this);
		}

		bidirectional_iterator  operator--(int)
		{
			bidirectional_iterator	old(*this);
			this->operator--();
			return (old);
		}

		//comparaison
		
		bool	operator==(const bidirectional_iterator &lhs) { return (this->_ptr == lhs._ptr); }
		bool	operator!=(const bidirectional_iterator &lhs) { return (this->_ptr != lhs._ptr); }
		
		template     <class Iter1, class Iter2>
		friend bool operator==(ft::bidirectional_iterator<Iter1, Node<Iter1> > const &lhs, ft::bidirectional_iterator<Iter2, Node<Iter2> > const &rhs);

		template     <class Iter1, class Iter2>
		friend bool operator!=(ft::bidirectional_iterator<Iter1, Node<Iter1> > const &lhs, ft::bidirectional_iterator<Iter2, Node<Iter2> > const &rhs);

		private:
		node_ptr    _ptr;
		node_ptr    _root;
		node_ptr    _nill;

	//el sucesor es el minimo de la brancha de la derecha
		node_ptr	successor(node_ptr node)
		{
			if (node->derecha != _nill)
				return (min(node->derecha));
			node_ptr y = node->padre;
			while (y != NULL && node == y->derecha)
			{
				node = y;
				y = y->padre;
			}
			if (y == NULL)
				return (_nill);
			return (y);
		}

		//el predecesor es el maximo de la brancha de la izquierda.
		node_ptr	predecessor(node_ptr node)
		{
			if (node->izquierda != _nill)
				return (max(node->izquierda));
			node_ptr y = node->padre;
			while (y != NULL && node == y->izquierda)
			{
				node = y;
				y = y->padre;
			}
			return (y);
		}

		node_ptr	min(node_ptr node)
		{
			while (node->izquierda != _nill)
				node = node->izquierda;
			return (node);
		}

		node_ptr	max(node_ptr node)
		{
			while (node->derecha != _nill)
				node = node->derecha;
			return (node);
		}
	};

	template <class Iter1, class Iter2>
	bool	operator==(ft::bidirectional_iterator<Iter1, Node<Iter1> > const &lhs, ft::bidirectional_iterator<Iter2, Node<Iter2> > const &rhs)
	{
		return (lhs._ptr == rhs._ptr);
	}

	template <class Iter1, class Iter2>
	bool	operator!=(ft::bidirectional_iterator<Iter1, Node<Iter1> > const &lhs, ft::bidirectional_iterator<Iter2, Node<Iter2> > const &rhs)
	{
		return (lhs._ptr != rhs._ptr);
	}
}
#endif
#ifndef MAP_HPP
# define MAP_HPP

#include "bidirectional_iterator.hpp"
#include "reverse_iterator.hpp"
#include "utils.hpp"
#include "RedBlack.hpp"
#include <iostream>

// doc
// -> https://www.lirmm.fr/~ducour/Doc-objets/ISO+IEC+14882-1998.pdf
// -> https://www.programiz.com/dsa/red-black-tree

namespace	ft
{
    template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key, T> > >
    class	map
    {
        public:
		/***********************************************************************************************************************/
		/** Member_types **/
		/***********************************************************************************************************************/
		typedef Key									key_type;
		typedef T									mapped_type;
		typedef pair<const key_type, mapped_type>	value_type;
		typedef Compare								key_compare;
		typedef Alloc								allocator_type;
		typedef typename Alloc::reference			reference;
		typedef typename Alloc::const_reference		const_reference;
		typedef typename Alloc::pointer				pointer;
		typedef typename Alloc::const_pointer		const_pointer;
		typedef Node<value_type>					node_type;
		typedef node_type*							node_ptr;
		typedef typename ft::bidirectional_iterator<value_type, node_type>				iterator;
		typedef typename ft::bidirectional_iterator<const value_type, const node_type>	const_iterator;
		typedef typename ft::reverse_iterator<iterator>									reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>							const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type					difference_type;
		typedef typename std::size_t													size_type;
		typedef ft::RedBlack<key_type, value_type, ft::selectFirst<value_type, key_type>, key_compare> tree_type;
		class value_compare;

		void			arbolin() const	{ this->_tree.print(); } //borrar
	// https://www.cs.usfca.edu/~galles/visualization/RedBlack.html ->pagina para ver los cambios

	/*(constructor)*/
		//empty (1)
		explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()):
		_alloc(alloc), _comp(comp), _tree() {}

		//range(2)
		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type()): _alloc(alloc), _comp(comp), _tree()
		{
			insert(first, last);
		}

		//copy(3)
		map(const map &cpy)
		{
			insert(cpy.begin(), cpy.end());
		}

		/*(destructor)*/
		virtual			~map(){} //nothing because except this->_tree is free with th destructor of RedBlack class

		map				&operator=(const map &cpy)
		{
			if(this != &cpy)
			{
				clear();
				this->_alloc = cpy._alloc;
				this->_comp = cpy._comp;
				this->insert(cpy.begin(), cpy.end());
			}
			return (*this);
		}

		/***********************************************************************************************************************/
		/** Iterators **/
		/***********************************************************************************************************************/

		/*(begin)*/
		iterator		begin()			{ return (iterator(this->_tree.min(),this->_tree.getRoot(), this->_tree.getNill())); }
		const_iterator	begin() const	{ return (const_iterator(this->_tree.min(), this->_tree.getRoot(), this->_tree.getNill())); }
		/*-------------------------------------------------------------------*/

		/*(end)*/
		iterator		end()			{ return (iterator(this->_tree.getNill(), this->_tree.getRoot(), this->_tree.getNill())); }
		const_iterator	end() const		{ return (const_iterator(this->_tree.getNill(), this->_tree.getRoot(), this->_tree.getNill())); }
		/*-------------------------------------------------------------------*/

		/*(rbigin)*/
		reverse_iterator		rbegin()		{ return (reverse_iterator(end())); }
		const_reverse_iterator	rbegin() const	{ return (const_reverse_iterator(end())); }
		/*-------------------------------------------------------------------*/

		/*(rend)*/
		reverse_iterator		rend()			{ return (reverse_iterator(begin()));}
		const_reverse_iterator	rend() const	{ return (const_reverse_iterator(begin())); }

		/***********************************************************************************************************************/
		/** Capacity **/
		/***********************************************************************************************************************/

		bool			empty() const		{ return (this->_tree.getSize() == 0); }
		size_type		size() const		{ return (this->_tree.getSize()); }
		size_type		max_size() const	{ return (this->_tree.max_size()); }



		/***********************************************************************************************************************/
		/** Elements access **/
		/***********************************************************************************************************************/

		mapped_type    &operator[] (const key_type &k)
		{
			node_ptr	node = this->_tree.search(k);
			if (node != this->_tree.getNill())
				return (node->data.second);
			this->_tree.insert(value_type(k, mapped_type()));
			node = this->_tree.search(k);
			return (node->data.second);
		}

		/***********************************************************************************************************************/
		/** Modifiers  **/
		/***********************************************************************************************************************/
		ft::pair<iterator,bool>	insert(const value_type &val)
		{
			bool    succes = this->_tree.insert(val);
			iterator    it = find(val.first);
			return (ft::pair<iterator, bool>(it, succes));
		}
		iterator				insert(iterator, const value_type &val) { return (insert(val).first); }

		template <class InputIterator>
		void					insert(InputIterator first, InputIterator last)
		{
			while(first != last)
				this->_tree.insert(*(first++));
		}

		void					erase(iterator position) { erase((*position).first); }

		size_type				erase(const key_type &k)
		{
			if(this->_tree.deleteNode(k))
				return (1);
			else
				return (0);       
		}

		void					erase(iterator first, iterator last)
		{
			while(first != last)
				erase(first++);
		}

		void					clear() { erase(begin(), end()); }
		
		void					swap( map &x) { this->_tree.swap(x._tree); }

		/***********************************************************************************************************************/
		/** Observers  **/
		/***********************************************************************************************************************/
		key_compare		key_comp() const	{ return (this->_comp); }
		value_compare	value_comp() const	{ return (value_compare(this->_comp)); }

		/***********************************************************************************************************************/
		/** Map operations  **/
		/***********************************************************************************************************************/
		iterator		find(const key_type &k)
		{
			node_ptr	node = this->_tree.search(k);
			if (node == this->_tree.getNill())
				return (end());
			return (iterator(node, this->_tree.getRoot(), this->_tree.getNill()));
		}
		const_iterator	find(const key_type &k) const
		{
			node_ptr	node = this->_tree.search(k);
			if (node == this->_tree.getNill())
				return (end());
			return (const_iterator(node, this->_tree.getRoot(), this->_tree.getNill()));
		}

		size_type		count(const key_type &k) const
		{
			node_ptr	node = this->_tree.search(k);
			if (node == this->_tree.getNill())
				return 0;
			return 1;
		}

		iterator		lower_bound(const key_type &k)
		{
			iterator	it = begin();
			while(it != end())
			{
				if (this->_comp((*it).first, k) == false)
					break;
				it++;
			}
			return (it);
		}

		const_iterator	lower_bound(const key_type &k) const
		{
			const_iterator	it = begin();
			while(it != end())
			{
				if (this->_comp((*it).first, k) == false)
					break;
				it++;
			}
			return (it);
		}

		iterator		upper_bound(const key_type &k)
		{
			iterator	it = begin();
			while(it != end())
			{
				if (this->_comp(k, (*it).first) == true)
					break;
				it++;
			}
			return (it);
		}

		const_iterator	upper_bound(const key_type &k) const
		{
			const_iterator	it = begin();
			while(it != end())
			{
				if (this->_comp(k, (*it).first) == true)
					break;
				it++;
			}
			return (it);
		}

		pair<iterator, iterator>	equal_range(const key_type &k)
		{
			return (ft::make_pair<iterator, iterator>(lower_bound(k), upper_bound(k)));
		}

		pair<const_iterator, const_iterator>	equal_range(const key_type &k) const
		{
			return (ft::make_pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k)));
		}
		/***********************************************************************************************************************/
		/** ALLOCATOR **/
		/***********************************************************************************************************************/
		allocator_type	get_allocator() const {return this->_alloc;}

		private:
		allocator_type		_alloc;
		key_compare			_comp;
		tree_type			_tree;

	};
	/***********************************************************************************************************************/
	/** OPERATORS RELATIONAL **/
	/***********************************************************************************************************************/
	template <class Key, class T, class Compare, class Alloc>
	bool	operator==(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	// not equal <==> !(==)
	template <class Key, class T, class Compare, class Alloc>
	bool	operator!=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return (!(rhs == lhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator<(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator>(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return (rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator<=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return (!(rhs < lhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator>=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return (!(lhs < rhs));
	}

	/***********************************************************************************************************************/
	/** Non-member functions **/
	/***********************************************************************************************************************/

	template <class Key, class T, class Compare, class Alloc>
	void	swap(map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y)
	{
		x.swap(y);
	}

	// https://www.cplusplus.com/reference/map/map/value_comp/
	template <class Key, class T, class Compare, class Alloc>
	class map<Key,T,Compare,Alloc>::value_compare
	{
		friend class map;
		
		protected:
		Compare comp;
			value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object

		public:
		typedef bool result_type;
		typedef value_type first_argument_type;
		typedef value_type second_argument_type;
		bool operator() (const value_type& x, const value_type& y) const
		{
			return comp(x.first, y.first);
		}
	};
}

#endif


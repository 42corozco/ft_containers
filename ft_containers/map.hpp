#ifndef MAP_HPP
# define MAP_HPP

# include <cstring>
# include <functional>
# include <memory>

// doc
// -> https://www.lirmm.fr/~ducour/Doc-objets/ISO+IEC+14882-1998.pdf
// -> https://www.programiz.com/dsa/red-black-tree

namespace	ft
{
	template<class Key, class T, class Compare = std::less<Key>,
		class Allocator = std::allocator<std::pair<const Key, T> >>
	class map
	{
		public:
		/***********************************************************************************************************************/
		/** Member_types **/
		/***********************************************************************************************************************/
		typedef key											key_type;
		typedef T											mapped_type;
		typedef	pair<const key_type, mapped_type>			value_type;
		typedef Compare										key_compare;
		//value_compare	Nested function class to compare elements	see value_comp
		typedef Allocator									allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;

/*
		typedef typename ft::bidirectional_iterator<value_type, node_type>				iterator;
		typedef typename ft::bidirectional_iterator<const value_type, const node_type>	const_iterator;

		typedef typename ft::reverse_iterator<iterator>			reverse_iterator;       // il faut le faire? 
		typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator; // il faut le faire? 
*/

		typedef typename iterator_traits<iterator>::difference_type	difference_type;
		typedef typename std::size_t								size_type;


/*
 *		//https://www.lirmm.fr/~ducour/Doc-objets/ISO+IEC+14882-1998.pdf -> page 490
		class value_compare : public binary_function<value_type,value_type,bool>
		{
			friend class map;
			protected:
			Compare comp;
			value_compare(Compare c) : comp(c) {}

			public:
			bool operator()(const value_type& x, const value_type& y) const { return comp(x.first, y.first); }
		};
*/

		/***********************************************************************************************************************/
		/** Member_functions **/
		/***********************************************************************************************************************/

		/*(constructor)*/
		//empty (1)
		/*
		explicit map (const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type());
		*/

		//range (2)
		/*
		template <class InputIterator>
		map (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type());
		*/


		//copy (3)
		//map(const map<Key,T,Compare,Allocator>& x); // en c++ sale el otro
		//map (const map& x);
		/*-------------------------------------------------------------------*/

		/*(destructor)*/
		~map(){};
		/*-------------------------------------------------------------------*/

		/*(operator =)*/
//		map& operator= (const map& x);


		/***********************************************************************************************************************/
		/** Iterators **/
		/***********************************************************************************************************************/

		/*(begin)*/
//		iterator				begin();
//		const_iterator			begin() const;
		/*-------------------------------------------------------------------*/

		/*(end)*/
//		iterator				end();
//		const_iterator			end() const;
		/*-------------------------------------------------------------------*/

		/*(rbigin)*/
//		reverse_iterator		rbegin();
//		const_reverse_iterator	rbegin() const;
		/*-------------------------------------------------------------------*/

		/*(rend)*/
//		iterator				rend();
//		const_iterator			rend() const;


		/***********************************************************************************************************************/
		/** Capacity **/
		/***********************************************************************************************************************/

		/*(empty)*/
//		bool		empty() const;
		/*-------------------------------------------------------------------*/

		/*(size)*/
//		size_type	size() const;
		/*-------------------------------------------------------------------*/

		/*(max_size)*/
//		size_type	max_size() const;


		/***********************************************************************************************************************/
		/** Elements access **/
		/***********************************************************************************************************************/

		/*(operator[])*/
//		T&	operator[](const key_type& x);


		/***********************************************************************************************************************/
		/** Modifiers  **/
		/***********************************************************************************************************************/

		/*(pair - single element(1))*/
//		pair<iterator, bool> insert(const value_type& x);

		/*(insert - with hint(2))*/
//		iterator	insert(iterator position, const value_type& x);

		/*(insert - range(3))*/
//		template <class InputIterator>
//		void		insert(InputIterator first, InputIterator last);
		/*-------------------------------------------------------------------*/

		/*(erase)*/
//		void		erase(iterator position);
//		size_type	erase(const key_type& x);
//		void		erase(iterator first, iterator last);
		/*-------------------------------------------------------------------*/

		/*(swap)*/
//		void		swap(map<Key,T,Compare,Allocator>&);
		/*-------------------------------------------------------------------*/

		/*(clear)*/
//		void		clear();


		/***********************************************************************************************************************/
		/** Observers  **/
		/***********************************************************************************************************************/

		/*(key_comp)*/
		// key_compare				key_comp() const;
		/*-------------------------------------------------------------------*/

		/*(value_comp)*/
		// value_compare			value_comp() const;


		/***********************************************************************************************************************/
		/** Map operations  **/
		/***********************************************************************************************************************/

		/*(find)*/
		// iterator			find(const key_type& x);
		// const_iterator		find(const key_type& x) const;
		/*-------------------------------------------------------------------*/

		/*(count)*/
		// size_type			count(const key_type& x) const;
		/*-------------------------------------------------------------------*/

		/*(lower_bound)*/
		// iterator			lower_bound(const key_type& x);
		// const_iterator		lower_bound(const key_type& x) const;
		/*-------------------------------------------------------------------*/

		/*(upper_bound)*/
		// iterator			upper_bound(const key_type& x);
		// const_iterator		upper_bound(const key_type& x) const;
		/*-------------------------------------------------------------------*/

		/*(equal_range (1))*/
//		pair<iterator,iterator>
//		equal_range(const key_type& x);

		/*(equal_range (2))*/
//		pair<const_iterator,const_iterator>
//		equal_range(const key_type& x) const;

		/***********************************************************************************************************************/
		/** get_allocator  **/
		/***********************************************************************************************************************/

		allocator_type get_allocator() const { return (_alloc); };


		private:
		allocator_type	_alloc;
	}
/*
	template <class Key, class T, class Compare, class Allocator>
	bool operator==(const map<Key,T,Compare,Allocator>& x,
	const map<Key,T,Compare,Allocator>& y);

	template <class Key, class T, class Compare, class Allocator>
	bool operator< (const map<Key,T,Compare,Allocator>& x,
	const map<Key,T,Compare,Allocator>& y);

	template <class Key, class T, class Compare, class Allocator>
	bool operator!=(const map<Key,T,Compare,Allocator>& x,
	const map<Key,T,Compare,Allocator>& y);

	template <class Key, class T, class Compare, class Allocator>
	bool operator> (const map<Key,T,Compare,Allocator>& x,
	const map<Key,T,Compare,Allocator>& y);

	template <class Key, class T, class Compare, class Allocator>
	bool operator>=(const map<Key,T,Compare,Allocator>& x,
	const map<Key,T,Compare,Allocator>& y);

	template <class Key, class T, class Compare, class Allocator>
	bool operator<=(const map<Key,T,Compare,Allocator>& x,
	const map<Key,T,Compare,Allocator>& y);

	// specialized algorithms:
	template <class Key, class T, class Compare, class Allocator>
	void swap(map<Key,T,Compare,Allocator>& x,
	map<Key,T,Compare,Allocator>& y);
*/
};

#endif

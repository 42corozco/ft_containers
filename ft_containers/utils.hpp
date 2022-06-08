#ifndef UTILS_HPP
# define UTILS_HPP

# include <sstream>

namespace ft
{
	/**********[enable_if]**********/
	//	->	https://h-deb.clg.qc.ca/Sujets/TrucsScouts/Comprendre_enable_if.html
	template<bool C, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T>	{ typedef T type; };
	/**********[fin-enable_if]**********/

	/**********[equal]**********/
	//	->	https://www.cplusplus.com/reference/algorithm/equal/
	template <class InputIterator1, class InputIterator2>
	bool equal (InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2)
	{
		while (first1!=last1)
		{
			if (!(*first1 == *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	};

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal (InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1!=last1)
		{
			if (!pred(*first1,*first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	};
	/**********[fin-equal]**********/

	/**********[lexicographical_compare]**********/
	//	->	https://en.cppreference.com/w/cpp/algorithm/lexicographical_compare
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 <* first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	};

	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2,Compare comp)
	{
		while ((first1 != last1) && (first2 != last2))
		{
			if (comp(*first1, *first2))
				return (true);
			if (comp(*first2, *first1))
				return (false);
			++first1;
			++first2;
		}
		return ((first1 == last1) && (first2 != last2));
	};
	/**********[finlexicographical_compare]**********/

	template <class Input, class Output>
	struct selectFirst : public std::unary_function<Input, Output>
	{
		const Output &operator()(const Input &x) const
		{
			return (x.first);
		}
	};

	/**********[PAIR]**********/
	// -> https://en.cppreference.com/w/cpp/utility/pair

    template<class T1, class T2>
	struct pair
	{
		//Member objects
		typedef T1	first_type;
		typedef T2	second_type;

		//member types
		first_type	first;
		second_type	second;

		//members functions
		pair() : first(first_type()), second(second_type()) {};
		template <class U, class V>
		pair(const pair<U,V> &pr) : first(pr.first), second(pr.second) {};
		pair(const first_type &a, const second_type &b) : first(a), second(b) {};

		pair	&operator=(const pair &pr)
		{
			first = pr.first;
			second = pr.second;
			return (*this);
		}
	};

	//(Non-member functions)
	template <class T1, class T2>
	ft::pair<T1, T2>	make_pair(T1 x, T2 y) { return (ft::pair<T1, T2>(x, y)); }

	template <class T1, class T2>
	bool	operator==(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return (lhs.first == rhs.first && lhs.second == rhs.second); }

	template <class T1, class T2>
	bool	operator!=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return (!(lhs == rhs)); }

	template <class T1, class T2>
	bool	operator<(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second)); }

	template <class T1, class T2>
	bool	operator<=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return (!(rhs < lhs)); }

	template <class T1, class T2>
	bool	operator>(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return (rhs < lhs); }

	template <class T1, class T2>
	bool	operator>=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return (!(lhs < rhs)); }
	/**********[FIN-PAIR]**********/
};

#endif

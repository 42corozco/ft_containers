#ifndef UTILS_HPP
# define UTILS_HPP

# include <sstream>

namespace ft
{
//https://h-deb.clg.qc.ca/Sujets/TrucsScouts/Comprendre_enable_if.html

	template<bool C, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T>	{ typedef T type; };



};

#endif

#include "vector.hpp"
#include <iostream>
#include <vector>

#define COLOR_ONE	"\033[35m"
#define COLOR_TWO	"\033[33m"
#define COLOR_NO	"\033[0m"

	template < typename T >
void	printf_v(T & v, std::string name)
{
	std::cout << name << " = {";
	for (unsigned int i = 0; i < v.size(); i++)
	{
		std::cout << v[i];
		if (i + 1 != v.size())
			std::cout << ", ";
	}
	std::cout << "}; \n";
}

int main()
{
	{
		// Create a vector containing integers
		std::cout << COLOR_TWO << "/--test MAX_SIZE size capacity--/" << COLOR_NO << std::endl;
		ft::vector<int>		m;
		std::vector<int>	v;

		std::cout << "MAX_SIZE: " << v.max_size() << "\n";
		std::cout << "max_size: " << m.max_size() << "\n";
		std::cout << "SIZE: " << v.size() << "\n";
		std::cout << "size: " << m.size() << "\n";
		std::cout << "CAPACITY: " << v.capacity() << "\n";
		std::cout << "capacity: " << m.capacity() << "\n";

		// Add two more integers to vector
		v.push_back(7);
		v.push_back(5);
		v.push_back(16);
		v.push_back(8);
		v.push_back(13);

		// Add two more integers to vector
		m.push_back(7);
		m.push_back(5);
		m.push_back(16);
		m.push_back(8);
		m.push_back(13);
		// Print out the vector
	
		printf_v(v, "v");
		printf_v(m, "m");
		std::cout << "MAX_SIZE: " << v.max_size() << "\n";
		std::cout << "max_size: " << m.max_size() << "\n";
		std::cout << "SIZE: " << v.size() << "\n";
		std::cout << "size: " << m.size() << "\n";
		std::cout << "CAPACITY: " << v.capacity() << "\n";
		std::cout << "capacity: " << m.capacity() << "\n";
	}
	{
		std::cout << COLOR_TWO << "/--test empty()--/" << COLOR_NO << std::endl;

		ft::vector<int> c;
		ft::vector<int> m (3,50);

		printf_v(c, "c");
		if (c.empty())
			std::cout << "vector c = empty" << std::endl;

		printf_v(m, "m");
		if (!m.empty())
			std::cout << "vector m != empty" << std::endl;
	}
	{
		std::cout << COLOR_TWO << "/--test get_allocator--/" << COLOR_NO << std::endl;
		ft::vector<int> myvector;
		int * p;
		unsigned int i;

		// allocate an array with space for 5 elements using vector's allocator:
		p = myvector.get_allocator().allocate(5);

		// construct values in-place on the array:
		for (i=0; i<5; i++) myvector.get_allocator().construct(&p[i],i);

		std::cout << "The allocated array contains:";
		for (i=0; i<5; i++) std::cout << ' ' << p[i];
		std::cout << '\n';

		// destroy and deallocate:
		for (i=0; i<5; i++) myvector.get_allocator().destroy(&p[i]);
		myvector.get_allocator().deallocate(p,5);
	}
	
	{
		std::cout << COLOR_TWO << "/--iterator verdadero--/" << COLOR_NO << std::endl;
		std::vector<int> myvector;
		for (int i=0; i<=10; i++) myvector.push_back(i);

		printf_v(myvector, "v");
		std::vector<int>::iterator it = myvector.begin();
		std::vector<int>::iterator at = myvector.end();
		std::vector<int>::reverse_iterator itt = myvector.rbegin();
		std::vector<int>::reverse_iterator att = myvector.rend();

		std::cout << &myvector << std::endl;
		std::cout << *it << " " << &it << std::endl;
		std::cout << *at << " " << &at << std::endl;
		std::cout << *itt << " " << &itt << std::endl;
		std::cout << *att << " " << &att << std::endl;
		std::cout << "max_size: " << myvector.max_size() << "\n";
		std::cout << "size: " << myvector.size() << "\n";
		std::cout << "capacity: " << myvector.capacity() << "\n";

		for (std::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}
	{
		std::cout << COLOR_TWO << "/--iterator mio--/" << COLOR_NO << std::endl;
		ft::vector<int> myvector;
		for (int i=0; i<=10; i++) myvector.push_back(i);

		printf_v(myvector, "v");
		ft::vector<int>::iterator it = myvector.begin();
		ft::vector<int>::iterator at = myvector.end();
		ft::vector<int>::reverse_iterator itt = myvector.rbegin();
		ft::vector<int>::reverse_iterator att = myvector.rend();

		std::cout << &myvector << std::endl;
		std::cout << *it << " " << &it << std::endl;
		std::cout << *at << " " << &at << std::endl;
		std::cout << *itt << " " << &itt << std::endl;
		std::cout << *att << " " << &att << std::endl;
		std::cout << "max_size: " << myvector.max_size() << "\n";
		std::cout << "size: " << myvector.size() << "\n";
		std::cout << "capacity: " << myvector.capacity() << "\n";

		for (ft::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << '\n';
	}
	{
		std::cout << COLOR_TWO << "/--test bool--/" << COLOR_NO << std::endl;
		ft::vector<int> foo (2,200);   // three ints with a value of 100
		ft::vector<int> bar (3,200);   // two ints with a value of 200

		if (foo==bar) std::cout << "1)foo and bar are equal\n";
		if (foo!=bar) std::cout << "2)foo and bar are not equal\n";
		if (foo< bar) std::cout << "3)foo is less than bar\n";
		if (foo> bar) std::cout << "4)foo is greater than bar\n";
		if (foo<=bar) std::cout << "5)foo is less than or equal to bar\n";
		if (foo>=bar) std::cout << "6)foo is greater than or equal to bar\n";
	}
	{
		std::cout << COLOR_TWO << "/--Clear--/" << COLOR_NO << std::endl;
		ft::vector<int> myvector(7,400);
		std::vector<int> stdvector(7,400);
		std::cout << "ft  - SIZE: " << myvector.size() << "\n";
		std::cout << "std - SIZE: " << stdvector.size() << "\n";
		std::cout << "ft  - CAPACITY: " << myvector.capacity() << "\n";
		std::cout << "std - CAPACITY: " << stdvector.capacity() << "\n";
		printf_v(myvector, "ft ");
		printf_v(stdvector, "std");
		myvector.clear();
		myvector.push_back (1101);
		myvector.push_back (2202);
		stdvector.clear();
		stdvector.push_back (1101);
		stdvector.push_back (2202);
		std::cout << "ft  - SIZE: " << myvector.size() << "\n";
		std::cout << "std - SIZE: " << stdvector.size() << "\n";
		std::cout << "ft  - CAPACITY: " << myvector.capacity() << "\n";
		std::cout << "std - CAPACITY: " << stdvector.capacity() << "\n";
		printf_v(myvector, "ft ");
		printf_v(stdvector, "std");
	}
	{
		std::cout << COLOR_TWO << "/--Iterator--/" << COLOR_NO << std::endl;
		ft::vector<int> numbers(6,10);
		std::vector<int> numbers2(6,10);

		printf_v(numbers, "ft ");
		printf_v(numbers2, "std");

		ft::vector<int>::iterator it = numbers.begin();
		ft::vector<int>::iterator itt = numbers.begin();
		std::vector<int>::iterator it2 = numbers2.begin();
		std::vector<int>::iterator itt2 = numbers2.begin();

		ft::vector<int>::iterator ult = numbers.end();
		std::vector<int>::iterator ult2 = numbers2.end();

		std::cout << "printf{ *it : ft } :" << *it << std::endl;
		std::cout << "printf{ *it :std } :"<< *it2 << std::endl;

		for (; it2 != ult2; it2++, (void)it++) //real
			std::cout << "std: {" << *it2 << "} ft: {" << *it << "}" << std::endl;
		for (; it != ult; itt++, (void)itt2++)
			std::cout << "ft: {" << *itt2 << "} ft: {" << *itt << "}" << std::endl;
	}
	{
		std::cout << COLOR_TWO << "/--Oper(+=)--/" << COLOR_NO << std::endl;
		ft::vector<int>	numbers(5, 42);
		std::vector<int>	numbers2(5, 42);

		numbers[0] = 0;
		numbers[1] = 2;
		numbers[2] = 33;
		numbers[3] = 3333;
		numbers[4] = 41;

		numbers2[0] = 0;
		numbers2[1] = 2;
		numbers2[2] = 33;
		numbers2[3] = 3333;
		numbers2[4] = 41;

		printf_v(numbers, "ft ");
		printf_v(numbers, "std");

		ft::vector<int>::iterator it = numbers.begin();
		std::vector<int>::iterator it2 = numbers2.begin();

		std::cout << "ft  = {" << *it;
		it += 2;
		std::cout << "} it += 2 {" << *it << "}";
		it -= 1;
		std::cout << " it -= 1 {" << *it << "}" << std::endl;

		std::cout << "std = {" << *it2;
		it2 += 2;
		std::cout << "} it += 2 {" << *it2 << "}";
		it2 -= 1;
		std::cout << " it -= 1 {" << *it2 << "}" << std::endl;

	}
	{
		std::cout << COLOR_TWO << "/--resize--/" << COLOR_NO << std::endl;
		std::vector<int> bar(3);
		ft::vector<int> bar2(3);

		bar[1] = 44;
		bar2[1] = 44;
		printf_v(bar, "std");
		printf_v(bar2, "ft ");
		bar.resize(10, 10);
		bar2.resize(10, 10);
		printf_v(bar, "std");
		printf_v(bar2, "ft ");
		bar.resize(2);
		bar2.resize(2);
		printf_v(bar, "std");
		printf_v(bar2, "ft ");

		std::cout << "SIZE: " << bar.size() << "\n";
		std::cout << "size: " << bar2.size() << "\n";
		std::cout << "CAPACITY: " << bar.capacity() << "\n";
		std::cout << "capacity: " << bar2.capacity() << "\n";
	}
	{
		std::cout << COLOR_TWO << "/--reserve--/" << COLOR_NO << std::endl;
		std::vector<int> bar(5,35);
		ft::vector<int> bar2(5,35);

		printf_v(bar, "std");
		printf_v(bar2, "ft ");
		std::cout << "CAPACITY: " << bar.capacity() << "\n";
		std::cout << "capacity: " << bar2.capacity() << "\n";
		std::cout << COLOR_ONE << "/--reserve 50--/" << COLOR_NO << std::endl;
		bar.reserve(50);
		bar2.reserve(50);
		std::cout << "CAPACITY: " << bar.capacity() << "\n";
		std::cout << "capacity: " << bar2.capacity() << "\n";
		std::cout << COLOR_ONE << "/--reserve 2--/" << COLOR_NO << std::endl;
		bar.reserve(2);
		bar2.reserve(2);
		std::cout << "CAPACITY: " << bar.capacity() << "\n";
		std::cout << "capacity: " << bar2.capacity() << "\n";
		printf_v(bar, "std");
		printf_v(bar2, "ft ");
	}
	{
		std::cout << COLOR_ONE << "/--reserve + push_back--/" << COLOR_NO << std::endl;
		ft::vector<int>::size_type sz;

		ft::vector<int> foo;
		sz = foo.capacity();
		std::cout << "making foo grow:\n";
		for (int i=0; i<8; ++i)
		{
			foo.push_back(i);
			if (sz!=foo.capacity())
				sz = foo.capacity();
			std::cout << i << " capacity: " << sz << " size: " << foo.size()<< '\n';
		}
	}
	{
		std::cout << COLOR_TWO << "/--assign--/" << COLOR_NO << std::endl;
		ft::vector<int> first;
		ft::vector<int> second;
		ft::vector<int> third;

		first.assign (7,100);             // 7 ints with a value of 100

		ft::vector<int>::iterator it;
		it=first.begin()+1;

		second.assign (it,first.end()-1); // the 5 central values of first

		int myints[] = {1776,7,4};
		third.assign(myints,myints+3);   // assigning from array.

		std::cout << "Size of first: " << int (first.size()) << '\n';
		std::cout << "Size of second: " << int (second.size()) << '\n';
		std::cout << "Size of third: " << int (third.size()) << '\n';

	}
	{
		std::cout << COLOR_TWO << "/--reference at--/" << COLOR_NO << std::endl;
		ft::vector<int> myvector (10);   // 10 zero-initialized ints

		// assign some values:
		for (unsigned i=0; i<myvector.size(); i++)
			myvector.at(i)=i;

		std::cout << "myvector contains:";
		for (unsigned i=0; i<myvector.size(); i++)
			std::cout << ' ' << myvector.at(i);
		std::cout << '\n';
		try
		{
			myvector.at(20);
		}
		catch(std::exception const& e)
		{
			std::cout << e.what() << "\n";
		}

	}
	{
		std::cout << COLOR_TWO << "/--reference front and back--/" << COLOR_NO << std::endl;
		ft::vector<int> myvector;

		myvector.push_back(78);
		myvector.push_back(16);

		// now front equals 78, and back 16
		myvector.front() -= myvector.back();
		std::cout << "myvector.front() is now " << myvector.front() << '\n';
	}
	{
		std::cout << COLOR_TWO << "/--Erase--/" << COLOR_NO << std::endl;
		ft::vector<int> myvector;
		std::vector<int> vector;

		// set some values (from 1 to 10)
		for (int i=1; i<=10; i++) myvector.push_back(i);
		for (int i=1; i<=10; i++) vector.push_back(i);
		// erase the 6th element
		printf_v(myvector, "ft ");
		printf_v(vector, "std");
		myvector.erase (myvector.begin());
		vector.erase (vector.begin());
		myvector.erase (myvector.begin()+5);
		vector.erase (vector.begin()+5);
		// erase the first 3 elements:
		printf_v(myvector, "ft ");
		printf_v(vector, "std");
		std::cout << COLOR_ONE<< "/--Erase(iterator,iterator)--/" << COLOR_NO << std::endl;
		vector.erase (vector.begin(), vector.begin()+3);
		printf_v(vector, "std");
		myvector.erase (myvector.begin(), myvector.begin()+3);
		printf_v(myvector, "ft ");
	}
/*	{
		std::cout << COLOR_ONE<< "/--swap--/" << COLOR_NO << std::endl;
		// vector container declaration
		ft::vector<int> myvector1;
		ft::vector<int> myvector2;

		for (int i=10; i>=1; i--) myvector1.push_back(i);
		for (int i=1; i<=10; i++) myvector2.push_back(i);
		printf_v(myvector1, "ori1 :");
		printf_v(myvector2, "ori2 :");
		// using swap() function to swap
		myvector1.swap(myvector2);

		// printing the first vector
		printf_v(myvector1, "swap1:");
		// printing the second vector
		printf_v(myvector2, "swap2:");
		return 0;
	}
*/
	{
		std::cout << COLOR_ONE<< "/--intento--/" << COLOR_NO << std::endl;
		ft::vector<std::string> vct(8);
		ft::vector<std::string> vct2;
		ft::vector<std::string>::iterator it = vct.begin();

		for (unsigned long int i = 0; i < vct.size(); ++i)
			it[i] = std::string((vct.size() - i), i + 65);
		printf_v(vct, "nani ");
		//printSize(vct, true);

		std::cout << "push_back():\n" << std::endl;

		vct.push_back("One long string");
		vct2.push_back("Another long string");

		printf_v(vct, "vct");
		printf_v(vct2, "vct2");

		vct.pop_back();
		vct2.pop_back();


		printf_v(vct, "vct");
		printf_v(vct2, "vct2");
		return (0);
	}
	return (0);
}

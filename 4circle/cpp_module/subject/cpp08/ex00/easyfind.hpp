#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <exception>

template<typename T>
typename T::iterator easyfind(T &p1, int num);

template<typename T>
typename T::iterator easyfind(T &p1, int num)
{
	typename T::iterator iter = p1.begin();
	for(; iter != p1.end(); iter++)
	{
		if(*iter == num)
			return iter;
	}
	throw std::exception();
}


#endif
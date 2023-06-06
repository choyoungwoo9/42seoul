#ifndef ITER_HPP
#define ITER_HPP

#include <iostream>

template <typename T1, typename T2>
void iter(T1 a, int len,  T2 func);

template <typename T>
void my_print(T a);

template <typename T1, typename T2>
void iter(T1 a, int len,  T2 func)
{
	for(int i = 0; i < len; i ++)
	{
		func(a[i]);
	}
}

template <typename T>
void my_print(T a)
{
	std::cout << a << std::endl;
}


#endif


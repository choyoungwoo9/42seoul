#include "iter.hpp"
#include <iostream>

int main()
{
	std::cout << "int test" << std::endl;
	int ar[5];
	for(int i = 0; i < 5; i ++)
		ar[i] = i;
	iter(ar, 5, my_print<int>);

	std::cout << "char test" << std::endl;
	char ar2[5];
	for(int i = 0; i < 5; i ++)
		ar2[i] = i+40;
	iter(ar2, 5, my_print<char>);

	std::cout << "void *test" << std::endl;
	void *ar3[5];
	for(int i = 0; i < 5; i ++)
		ar3[i] = ar3 + i;
	iter(ar3, 5, my_print<void *>);

	std::cout << "float test" << std::endl;
	float ar4[5];
	for(int i = 0; i < 5; i ++)
		ar4[i] = i + 0.1f;
	iter(ar4, 5, my_print<float>);

	std::cout << "bool test" << std::endl;
	bool ar5[5];
	for(int i = 0; i < 5; i ++)
		ar5[i] = i % 2;
	iter(ar5, 5, my_print<bool>);
}

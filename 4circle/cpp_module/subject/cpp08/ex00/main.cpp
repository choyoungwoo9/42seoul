#include <vector>
#include <deque>
#include <iostream>

#include "easyfind.hpp"

int main()
{
	std::vector<int> v1;
	for(int i = 1; i <= 5; i ++)
	{
		v1.push_back(i);
	}
	try
	{
		std::vector<int>::iterator it = easyfind<std::vector<int> >(v1, 3);
		std::cout << *it << std::endl;
		std::cout << ++*it << std::endl;
		std::cout << ++*it << std::endl;
		it = easyfind<std::vector<int> >(v1, 6);
		std::cout << *it << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	std::deque<int> d1;
	for(int i = 1; i <= 5; i ++)
	{
		d1.push_back(i);
	}
	try
	{
		std::deque<int>::iterator it = easyfind<std::deque<int> >(d1, 3);
		std::cout << *it << std::endl;
		std::cout << ++*it << std::endl;
		std::cout << ++*it << std::endl;
		it = easyfind<std::deque<int> >(d1, 6);
		std::cout << *it << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}
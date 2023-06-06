#include "MutentStack.hpp"
#include <iostream>
#include <list>

void test1()
{
	MutantStack<int> mstack;
	mstack.push(5); 
	mstack.push(17);
	std::cout << mstack.top() << std::endl;
	mstack.pop();
	std::cout << mstack.size() << std::endl;
	mstack.push(3); 
	mstack.push(5); 
	mstack.push(737); //[...] mstack.push(0);
	MutantStack<int>::iterator it = mstack.begin(); 
	MutantStack<int>::iterator ite = mstack.end();

	++it;
	--it;
	while (it != ite) 
	{
	    std::cout << *it << std::endl;
		++it; 
	}
	std::stack<int> s(mstack);
}

void test2()
{
	std::list<int> mstack;
	mstack.push_back(5); 
	mstack.push_back(17);
	std::cout << mstack.back() << std::endl;
	mstack.pop_back();
	std::cout << mstack.size() << std::endl;
	mstack.push_back(3); 
	mstack.push_back(5); 
	mstack.push_back(737); //[...] mstack.push(0);
	std::list<int>::iterator it = mstack.begin(); 
	std::list<int>::iterator ite = mstack.end();

	++it;
	--it;
	while (it != ite) 
	{
	    std::cout << *it << std::endl;
		++it; 
	}

	//std::stack<int> s(mstack);
}


void test3()
{
	MutantStack<int> mstack;
	mstack.push(1);
	mstack.push(2);
	std::cout << mstack.top() << std::endl;

	std::cout << "just_iter" << std::endl;
	for(MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); it ++)
		std::cout << *it << " ";
	std::cout << std::endl;

	std::cout << "iter_change" << std::endl;
	MutantStack<int>::iterator it1 = mstack.begin();
	*it1 = 3;
	for(MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); it ++)
		std::cout << *it << " ";
	std::cout << std::endl;


	std::cout << "const_iter" << std::endl;
	MutantStack<int>::const_iterator it = mstack.begin();
	for(; it != mstack.end(); it ++)
		std::cout << *it << " ";
	std::cout << std::endl;
	//*it = 3;

	std::cout << "reverse_iter" << std::endl;
	for(MutantStack<int>::reverse_iterator rit = mstack.rbegin(); rit != mstack.rend(); rit++)
		std::cout << *rit << " ";
	std::cout << std::endl;
}

int main()
{
	std::cout << "test1" << std::endl;
	test1();
	std::cout << "test2" << std::endl;
	test2();
	//std::cout << "reverse_iter" << std::endl;
	//test3();
	return 0;
}
#include <iostream>
#include <vector>

#include "Span.hpp"

int main()
{

	Span sp = Span(5);
	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);

	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;


	try
	{
		Span sp2 = Span(100000);
		std::vector<int> v(100000);
		for(unsigned int i = 0;i < v.size(); i++)
			v[i] = i*2;
		sp2.addNumbers<std::vector<int>::iterator >(v.begin(), v.end());
		std::cout << sp2.shortestSpan() << std::endl;
		std::cout << sp2.longestSpan() << std::endl;
		sp2.addNumber(10001);
	}
	catch(std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;

}
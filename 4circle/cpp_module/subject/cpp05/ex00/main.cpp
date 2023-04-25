#include "Bureaucrat.hpp"
#include <iostream>

void test(std::string str, int grade)
{
	try
	{
		Bureaucrat ins(str, grade);
		std::cout << ins << std::endl;
		ins.increment();
		ins.decrement();
		ins.decrement();
		std::cout << ins << std::endl;
	}
	catch(std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

int main()
{
		test("youngwch1", 50);
		test("youngwch2", 151);
		test("youngwch3", 1);
		test("youngwch4", 150);
}

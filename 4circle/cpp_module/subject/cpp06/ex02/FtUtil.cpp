#include "FtUtil.hpp"

Base *generate(void)
{
	Base *ret = NULL;
	std::srand(static_cast<unsigned int>(std::clock()));
	//std::cout << std::clock() << std::endl;
	int random_num = std::rand();
	if(random_num % 3 == 0)
	{
		//std::cout << "A\n";
		ret = new A();
	}
	else if(random_num % 3 == 1)
	{
		//std::cout << "B\n";
		ret = new B();
	}
	else if(random_num % 3 == 2)
	{
		//std::cout << "C\n";
		ret = new C();
	}
	return ret;
}

void identify(Base* p)
{
	Base *check;
	//not null
	check = p;
	check = dynamic_cast<A*>(p);
	if(check)
		std::cout << 'A' << std::endl;
	check = dynamic_cast<B*>(p);
	if(check)
		std::cout << 'B' << std::endl;
	check = dynamic_cast<C*>(p);
	if(check)
		std::cout << 'C' << std::endl;
}
void identify(Base& p)
{
	try
	{
		static_cast<void>(dynamic_cast<A&>(p));
		std::cout << 'A' << std::endl;
	}
	catch(const std::exception& e)
	{
		//std::cout << e.what() << '\n';
	}
	try
	{
		static_cast<void>(dynamic_cast<B&>(p));
		std::cout << 'B' << std::endl;
	}
	catch(const std::exception& e)
	{
		//std::cout << e.what() << '\n';
	}
	try
	{
		static_cast<void>(dynamic_cast<C&>(p));
		std::cout << 'C' << std::endl;
	}
	catch(const std::exception& e)
	{
		//std::cout << e.what() << '\n';
	}
}

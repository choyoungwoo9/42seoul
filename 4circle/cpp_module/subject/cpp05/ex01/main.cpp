#include "Bureaucrat.hpp"
#include "Form.hpp"

int main()
{
	try
	{
		Form f1("f1", 33, 22);
		std::cout << f1 << std::endl;
		Form f2("f2", 151, 22);
		std::cout << f2 << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	
	// try
	// {
	// 	Form f1("f1", 33, 22);
	// 	std::cout << f1 << std::endl;
	// 	Bureaucrat youngwch("youngwch", 33);
	// 	youngwch.signForm(f1);
	// 	Form f2("f2", 33, 22);
	// 	youngwch.decrement();
	// 	youngwch.signForm(f2);
	// }
	// catch(std::exception &e)
	// {
	// 	std::cout << e.what() << std::endl;
	// }
	
// 	try
// 	{
// 		Form f1("f1", 33, 22);
// 		std::cout << f1 << std::endl;
// 		Bureaucrat youngwch("youngwch", 33);
// 		youngwch.signForm(f1);
// 		youngwch.signForm(f1);
// 		Bureaucrat youngwch2("youngwch2", 0);
// 	}
// 	catch(std::exception &e)
// 	{
// 		std::cout << e.what() << std::endl;
// 	}
}

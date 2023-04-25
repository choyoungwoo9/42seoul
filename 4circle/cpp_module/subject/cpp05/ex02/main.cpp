#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

void sh_test()
{
	std::cout << "sh_test start" << std::endl;
	try
	{
		Bureaucrat B144("B144", 144);
		std::cout << B144 << std::endl;
		Bureaucrat B137("B137", 137);
		ShrubberyCreationForm S("S");
		std::cout << S << std::endl;
		B144.signForm(S);
		std::cout << S << std::endl;
		B137.executeForm(S);
		B144.executeForm(S);
    }
    catch(const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
	std::cout << "sh_test end" << std::endl;
}

void rob_test()
{
	std::cout << "rob_test start" << std::endl;
	try
    {
        Bureaucrat B72("B72", 72);
        Bureaucrat B45("B45", 45);
        RobotomyRequestForm R("R");
        B72.signForm(R);
		B45.executeForm(R);
		B72.executeForm(R);
    }
    catch(const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
	std::cout << "rob_test end" << std::endl;
}

void pr_test()
{
	std::cout << "pr_test start" << std::endl;
	try
    {
		Bureaucrat B25("B25", 25);
        Bureaucrat B5("B5", 5);
        PresidentialPardonForm P("P");
       	B25.signForm(P);
        B5.executeForm(P);
		B25.executeForm(P);
    }
    catch(const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
	std::cout << "pr_test end" << std::endl;
}

void exception_test()
{
	std::cout << "ex_test start" << std::endl;
	try
	{
		//AForm A("A", 3, 3);
		//Bureaucrat B("B", 151);
		//Bureaucrat B("B", 0);
		Bureaucrat A("B", 1);
		A.increment();
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << "ex_test end" << std::endl;
}

int main()
{
	sh_test();
	//rob_test();
	//pr_test();
	//exception_test();
}

#include "Bureaucrat.hpp"
#include "Form.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "Intern.hpp"

int main()
{
	Form *form = NULL;
	try
	{
		Intern I;
		form = I.makeForm("shrubbery creation", "bender");
		Bureaucrat B("B", 137);
		B.signForm(*form);
		B.executeForm(*form);
		delete form;
		form = NULL;
	}
	catch(std::exception &e)
	{
		std::cout << e.what() << std::endl;
		if(form)
		{
			delete form;
			form = NULL;
		}
	}
	try
	{
		Intern I;
		Form *form = I.makeForm("robotomy request", "bender");
		Bureaucrat B("B", 45);
		B.signForm(*form);
		B.executeForm(*form);
		delete form;
		form = NULL;
	}
	catch(std::exception &e)
	{
		std::cout << e.what() << std::endl;
		if(form)
		{
			delete form;
			form = NULL;
		}
	}

	try
	{
		Intern I;
		Form *form = I.makeForm("presidential pardon", "bender");
		Bureaucrat B("B", 5);
		B.signForm(*form);
		B.executeForm(*form);
		delete form;
		form = NULL;
	}
	catch(std::exception &e)
	{
		std::cout << e.what() << std::endl;
		if(form)
		{
			delete form;
			form = NULL;
		}
	}

	try
	{
		Intern I;
		Form *form = I.makeForm("dd", "bender");
		Bureaucrat B("B", 5);
		B.signForm(*form);
		B.executeForm(*form);
		delete form;
		form = NULL;
	}
	catch(std::exception &e)
	{
		std::cout << e.what() << std::endl;
		if(form)
		{
			delete form;
			form = NULL;
		}
	}
	//system("leaks at_least");
}

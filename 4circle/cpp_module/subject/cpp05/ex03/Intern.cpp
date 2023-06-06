#include "Intern.hpp"

Intern::Intern()
{

}
Intern::~Intern()
{

}
Intern::Intern(Intern &param)
{
	*this = param;
}
Intern &Intern::operator =(Intern &param)
{
	(void) param;
	return *this;
}
Form *Intern::makeForm(std::string form, std::string name)
{
	Form *ret;

	if(form == "shrubbery creation")
	{
		ret = new ShrubberyCreationForm(name);
		std::cout << "Intern creates ShrubberyCreationForm" << std::endl;
	}
	if(form == "robotomy request")
	{
		ret = new RobotomyRequestForm(name);
		std::cout << "Intern creates RobotomyRequestForm" << std::endl;
	}
	if(form == "presidential pardon")
	{
		ret = new PresidentialPardonForm(name);
		std::cout << "Intern creates PresidentialPardonForm" << std::endl;
	}
	if(form != "presidential pardon" && form != "robotomy request" && form != "shrubbery creation")
		throw NotMatchException();
	return ret;
}


const char* Intern::NotMatchException::what() const throw()
{
	return "this Form not match anything!";
}

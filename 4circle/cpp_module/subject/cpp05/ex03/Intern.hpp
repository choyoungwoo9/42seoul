#ifndef INTERN_HPP
#define INTERN_HPP

#include "Form.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

#include <string>
#include <exception>
class Intern
{
	public:
		class NotMatchException : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};
		Intern();
		~Intern();
		Intern(Intern &param);
		Intern &operator =(Intern &param);
		Form *makeForm(std::string form, std::string name);
};

#endif

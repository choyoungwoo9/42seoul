#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP

#include "AForm.hpp"
#include <fstream>
#include <iostream>

class ShrubberyCreationForm : public AForm
{
	private:
		ShrubberyCreationForm();
		ShrubberyCreationForm &operator =(ShrubberyCreationForm &param);
		ShrubberyCreationForm(ShrubberyCreationForm &param);
	public:
		virtual ~ShrubberyCreationForm();
		ShrubberyCreationForm(std::string name);
		virtual void execute(Bureaucrat const &executor) const;
};

#endif
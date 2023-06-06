#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP

#include "Form.hpp"
#include <fstream>
#include <iostream>

class ShrubberyCreationForm : public Form
{
	private:
		ShrubberyCreationForm();
		ShrubberyCreationForm(ShrubberyCreationForm &param);
		ShrubberyCreationForm &operator =(ShrubberyCreationForm &param);
	public:
		virtual ~ShrubberyCreationForm();
		ShrubberyCreationForm(std::string name);
		virtual void execute(Bureaucrat const &executor) const;
};

#endif
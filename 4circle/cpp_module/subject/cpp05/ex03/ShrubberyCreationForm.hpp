#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP

#include "Form.hpp"
#include <fstream>
#include <iostream>

class ShrubberyCreationForm : public Form
{
	private:
		ShrubberyCreationForm();
	public:
		virtual ~ShrubberyCreationForm();
		ShrubberyCreationForm(ShrubberyCreationForm &param);
		ShrubberyCreationForm &operator =(ShrubberyCreationForm &param);
		ShrubberyCreationForm(std::string name);
		virtual void execute(Bureaucrat const &executor) const;
};

#endif
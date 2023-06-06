#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include "Form.hpp"
#include <cstdlib>
#include <iostream>
#include <ctime>

class RobotomyRequestForm : public Form
{
	private:
		RobotomyRequestForm();
		RobotomyRequestForm(RobotomyRequestForm &param);
		RobotomyRequestForm &operator =(RobotomyRequestForm &param);
	public:
		virtual ~RobotomyRequestForm();
		RobotomyRequestForm(std::string name);
		virtual void execute(Bureaucrat const &executor) const;
};

#endif
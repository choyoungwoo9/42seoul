#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include "AForm.hpp"
#include <cstdlib>
#include <iostream>
#include <ctime>

class RobotomyRequestForm : public AForm
{
	private:
		RobotomyRequestForm();
	public:
		virtual ~RobotomyRequestForm();
		RobotomyRequestForm(RobotomyRequestForm &param);
		RobotomyRequestForm &operator =(RobotomyRequestForm &param);
		RobotomyRequestForm(std::string name);
		virtual void execute(Bureaucrat const &executor) const;
};

#endif
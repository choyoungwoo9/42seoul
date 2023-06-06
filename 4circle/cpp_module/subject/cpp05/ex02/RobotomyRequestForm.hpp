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
		RobotomyRequestForm &operator =(RobotomyRequestForm &param);
		RobotomyRequestForm(RobotomyRequestForm &param);
	public:
		virtual ~RobotomyRequestForm();
		RobotomyRequestForm(std::string name);
		virtual void execute(Bureaucrat const &executor) const;
};

#endif
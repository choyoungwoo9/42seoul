#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm()
:AForm("default", 72, 45)
{

}
RobotomyRequestForm::~RobotomyRequestForm()
{

}
RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm &param)
:AForm(param.getName(), 72, 45)
{
	*this = param;
}
RobotomyRequestForm &RobotomyRequestForm::operator =(RobotomyRequestForm &param)
{
	param.getName();
	return *this;
}
RobotomyRequestForm::RobotomyRequestForm(std::string name)
:AForm(name, 72, 45)
{
}
void RobotomyRequestForm::execute(Bureaucrat const &executor) const
{
	if(!this->getSign())
		throw NoSignedException();
	if(this->getExecuteGrade() < executor.getGrade())
		throw GradeTooLowException();
	std::cout << "DRILLLLLLLLLLLLLLLL" << std::endl;
	std::srand(std::time(nullptr));
	if(std::rand() % 2)
	{
		std::cout << this->getName() << " has been robotomized successfully" << std::endl;
	}
	else
	{
		std::cout << this->getName() << " has failed to be robotomized" << std::endl;
	}
}

#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm()
:Form("default", 72, 45)
{

}
RobotomyRequestForm::~RobotomyRequestForm()
{

}
RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm &param)
:Form(param.getName(), 72, 45)
{
	*this = param;
}
RobotomyRequestForm &RobotomyRequestForm::operator =(RobotomyRequestForm &param)
{
	param.getName();
	return *this;
}
RobotomyRequestForm::RobotomyRequestForm(std::string name)
:Form(name, 72, 45)
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

#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm()
:AForm("default", 25, 5)
{
}
PresidentialPardonForm::~PresidentialPardonForm()
{
}
PresidentialPardonForm::PresidentialPardonForm(PresidentialPardonForm &param)
:AForm(param.getName(), 25, 5)
{
	*this = param;
}
PresidentialPardonForm &PresidentialPardonForm::operator =(PresidentialPardonForm &param)
{
	param.getName();
	return *this;
}
PresidentialPardonForm::PresidentialPardonForm(std::string name)
:AForm(name, 25, 5)
{
}
void PresidentialPardonForm::execute(Bureaucrat const &executor) const
{
	if(!this->getSign())
		throw NoSignedException();
	if(this->getExecuteGrade() < executor.getGrade())
		throw GradeTooLowException();
	std::cout << this->getName() << " has been pardoned by Zaphod Beeblebrox" << std::endl;
}

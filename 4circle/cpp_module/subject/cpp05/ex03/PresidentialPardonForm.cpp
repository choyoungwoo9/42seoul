#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm()
:Form("default", 25, 5)
{
}
PresidentialPardonForm::~PresidentialPardonForm()
{
}
PresidentialPardonForm::PresidentialPardonForm(PresidentialPardonForm &param)
:Form(param.getName(), 25, 5)
{
	*this = param;
}
PresidentialPardonForm &PresidentialPardonForm::operator =(PresidentialPardonForm &param)
{
	param.getName();
	return *this;
}
PresidentialPardonForm::PresidentialPardonForm(std::string name)
:Form(name, 25, 5)
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

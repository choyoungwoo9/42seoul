#include "AForm.hpp"

AForm::AForm()
:name("default"), sign(false), signed_grade(150), execute_grade(150)
{
}

AForm::~AForm()
{
}
AForm::AForm(const AForm &param)
:name(param.name), sign(param.sign), signed_grade(param.signed_grade), execute_grade(param.execute_grade)
{
}
AForm &AForm::operator =(const AForm &param)
{
	(void)param;
	return *this;
}

AForm::AForm(std::string name, int p_signed_grade, int p_execute_grade)
:name(name), sign(false), signed_grade(p_signed_grade), execute_grade(p_execute_grade)
{
	if(p_signed_grade < 1 || p_execute_grade < 1)
		throw GradeTooHighException();
	if(p_signed_grade > 150 || p_execute_grade > 150)
		throw GradeTooLowException();
}

void AForm::beSigned(Bureaucrat &param)
{
	if(signed_grade < param.getGrade())
	{
		throw(GradeTooLowException());
	}
	else if(this->getSign())
	{
		throw(AlreadySignedException());
	}
	this->sign = true;
}
const std::string &AForm::getName() const
{
	return this->name;
}
bool AForm::getSign() const
{
	return this->sign;
}
int AForm::getSignedGrade() const
{
	return this->signed_grade;
}
int AForm::getExecuteGrade() const
{
	return this->execute_grade;
}

const char *AForm::GradeTooHighException::what() const throw()
{
	return "Grade too high !";
}

const char *AForm::GradeTooLowException::what() const throw()
{
	return "Grade too low !";
}

const char* AForm::AlreadySignedException::what() const throw()
{
	return "Already this form signed !";
}

const char* AForm::NoSignedException::what() const throw()
{
	return "this Form need sign!";
}

std::ostream &operator<<(std::ostream &out, const AForm &bc)
{
    out << "name : " << bc.getName() << " signed : " << bc.getSign();
	out << " sign require : " << bc.getSignedGrade() << " execute require : " << bc.getExecuteGrade();
	return (out);
}
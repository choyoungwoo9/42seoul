#include "Form.hpp"

Form::Form()
:name("default"), sign(false), signed_grade(150), execute_grade(150)
{
}

Form::~Form()
{
}
Form::Form(const Form &param)
:name(param.name), sign(param.sign), signed_grade(param.signed_grade), execute_grade(param.execute_grade)
{
}
Form &Form::operator =(const Form &param)
{
	(void)param;
	return *this;
}

Form::Form(std::string name, int p_signed_grade, int p_execute_grade)
:name(name), sign(false), signed_grade(p_signed_grade), execute_grade(p_execute_grade)
{
	if(p_signed_grade < 1 || p_execute_grade < 1)
		throw GradeTooHighException();
	if(p_signed_grade > 150 || p_execute_grade > 150)
		throw GradeTooLowException();
}

void Form::beSigned(Bureaucrat &param)
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
const std::string &Form::getName() const
{
	return this->name;
}
bool Form::getSign() const
{
	return this->sign;
}
int Form::getSignedGrade() const
{
	return this->signed_grade;
}
int Form::getExecuteGrade() const
{
	return this->execute_grade;
}

const char *Form::GradeTooHighException::what() const throw()
{
	return "Grade too high !";
}

const char *Form::GradeTooLowException::what() const throw()
{
	return "Grade too low !";
}

const char* Form::AlreadySignedException::what() const throw()
{
	return "Already this form signed !";
}

const char* Form::NoSignedException::what() const throw()
{
	return "this Form need sign!";
}

std::ostream &operator<<(std::ostream &out, const Form &bc)
{
    out << "name : " << bc.getName() << " signed : " << bc.getSign();
	out << " sign require : " << bc.getSignedGrade() << " execute require : " << bc.getExecuteGrade();
	return (out);
}
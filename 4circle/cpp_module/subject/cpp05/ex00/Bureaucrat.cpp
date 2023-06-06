#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat()
:name("default"), grade(100)
{
	if(grade < 1)
		throw GradeTooHighException();
	if(grade > 150)
		throw GradeTooLowException();
}
Bureaucrat::~Bureaucrat()
{

}
Bureaucrat::Bureaucrat(const Bureaucrat &param)
:name(param.name), grade(param.grade)
{
	if(grade < 1)
		throw GradeTooHighException();
	if(grade > 150)
		throw GradeTooLowException();
}
Bureaucrat &Bureaucrat::operator =(const Bureaucrat &param)
{
	this->grade = param.grade;
	return *this;
}

Bureaucrat::Bureaucrat(const std::string name, int grade)
:name(name), grade(grade)
{
	if(grade < 1)
		throw GradeTooHighException();
	if(grade > 150)
		throw GradeTooLowException();
}

const std::string &Bureaucrat::getName() const
{
	return this->name;
}

int Bureaucrat::getGrade() const
{
	return this->grade;
}

void Bureaucrat::increment()
{
	grade --;
	if(grade < 1)
	{
		grade ++;
		throw GradeTooHighException();
	}
}

void Bureaucrat::decrement()
{
	grade ++;
	if(grade > 150)
	{
		grade --;
		throw GradeTooLowException();	
	}
}

const char *Bureaucrat::GradeTooHighException::what() const throw()
{
	return "Grade too high !";
}

const char *Bureaucrat::GradeTooLowException::what() const throw()
{
	return "Grade too low !";
}

std::ostream &operator<<(std::ostream &out, const Bureaucrat &bc)
{
    out << bc.getName() << ", Bureaucrat grade " << bc.getGrade() << ".";
    return (out);
}
#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <string>
#include <iostream>
class Form;

class Bureaucrat
{
	public:
		class GradeTooHighException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
		class GradeTooLowException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
		Bureaucrat();
		~Bureaucrat();
		Bureaucrat(const std::string param, int grade);
		Bureaucrat(const Bureaucrat &param);
		void increment();
		void decrement();
		const std::string &getName() const;
		int getGrade() const;
		void signForm(Form &param);
		void executeForm(Form& param);
	private:
		Bureaucrat &operator =(const Bureaucrat &param);
		const std::string name;
		int grade;
};

std::ostream &operator<<(std::ostream &out, const Bureaucrat &bc);

#endif
#ifndef FORM_HPP
#define FORM_HPP

#include "Bureaucrat.hpp"

#include <string>
#include <iostream>
#include <exception>

class Form
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
		class AlreadySignedException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
		class NoSignedException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
		Form();
		virtual ~Form();
		Form(const Form &param);
		Form(std::string name, int p_signed_grade, int p_execute_grade);
		void beSigned(Bureaucrat &param);
		const std::string & getName() const;
		bool getSign() const;
		int getSignedGrade() const;
		int getExecuteGrade() const;
		virtual void execute(Bureaucrat const &executor) const = 0;
	private:
		const std::string name;
		bool sign;
		const int signed_grade;
		const int execute_grade;
		Form &operator =(const Form &param);
};

std::ostream &operator<<(std::ostream &out, const Form &bc);
#endif
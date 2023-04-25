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
		Form();
		~Form();
		Form(const Form &param);
		Form(std::string name, int p_signed_grade, int p_execute_grade);
		void beSigned(Bureaucrat &param);
		const std::string & getName() const;
		bool getSign() const;
		int getSignedGrade() const;
		int getExecuteGrade() const;
	private:
		const std::string name;
		bool sign;
		const int sign_grade;
		const int execute_grade;
		Form &operator =(const Form &param);
};

std::ostream &operator<<(std::ostream &out, const Form &bc);

#endif
#ifndef AFORM_HPP
#define AFORM_HPP

#include "Bureaucrat.hpp"

#include <string>
#include <iostream>
#include <exception>

class AForm
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
		AForm();
		virtual ~AForm();
		AForm(const AForm &param);
		AForm(std::string name, int p_signed_grade, int p_execute_grade);
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
		AForm &operator =(const AForm &param);
};

std::ostream &operator<<(std::ostream &out, const AForm &bc);
#endif
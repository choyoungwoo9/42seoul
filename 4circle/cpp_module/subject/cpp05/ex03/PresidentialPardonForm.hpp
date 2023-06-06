#ifndef PRESIDENRIALPARDONFORM_HPP
#define PRESIDENRIALPARDONFORM_HPP

#include "Form.hpp"

class PresidentialPardonForm : public Form
{
	private:
		PresidentialPardonForm();
		PresidentialPardonForm(PresidentialPardonForm &param);
		PresidentialPardonForm &operator =(PresidentialPardonForm &param);
	public:
		virtual ~PresidentialPardonForm();
		PresidentialPardonForm(std::string name);
		virtual void execute(Bureaucrat const &executor) const;
};
#endif
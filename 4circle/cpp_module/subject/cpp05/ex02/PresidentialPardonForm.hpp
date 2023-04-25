#ifndef PRESIDENRIALPARDONFORM_HPP
#define PRESIDENRIALPARDONFORM_HPP

#include "AForm.hpp"

class PresidentialPardonForm : public AForm
{
	private:
		PresidentialPardonForm();
	public:
		virtual ~PresidentialPardonForm();
		PresidentialPardonForm(PresidentialPardonForm &param);
		PresidentialPardonForm &operator =(PresidentialPardonForm &param);
		PresidentialPardonForm(std::string name);
		virtual void execute(Bureaucrat const &executor) const;
};
#endif
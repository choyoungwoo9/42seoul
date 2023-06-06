#ifndef PRESIDENRIALPARDONFORM_HPP
#define PRESIDENRIALPARDONFORM_HPP

#include "AForm.hpp"

class PresidentialPardonForm : public AForm
{
	private:
		PresidentialPardonForm();
		PresidentialPardonForm &operator =(PresidentialPardonForm &param);
		PresidentialPardonForm(PresidentialPardonForm &param);
	public:
		virtual ~PresidentialPardonForm();
		PresidentialPardonForm(std::string name);
		virtual void execute(Bureaucrat const &executor) const;
};
#endif
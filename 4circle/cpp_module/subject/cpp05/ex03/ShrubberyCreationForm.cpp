#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm()
:Form("default", 145, 137)
{

}
ShrubberyCreationForm::~ShrubberyCreationForm()
{

}
ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm &param)
:Form(param.getName(), 145, 137)
{
	*this = param;
}
ShrubberyCreationForm &ShrubberyCreationForm::operator =(ShrubberyCreationForm &param)
{
	param.getName();
	return *this;
}
ShrubberyCreationForm::ShrubberyCreationForm(std::string name)
:Form(name, 145, 137)
{
}
void ShrubberyCreationForm::execute(Bureaucrat const &executor) const
{
	if(!this->getSign())
		throw NoSignedException();
	if(this->getExecuteGrade() < executor.getGrade())
		throw GradeTooLowException();
	std::ofstream ofile(this->getName() + "_shrubbery");
	if(!ofile.is_open())
		return ;
    ofile	<< "         /\\\n"
			<< "        <  >\n"
			<< "         \\/\n"
			<< "         /\\\n"
			<< "        /  \\\n"
			<< "       /++++\\\n"
			<< "      /  ()  \\\n"
			<< "     /--------\\\n"
			<< "    /          \\\n"
			<< "   /____________\\\n";
	ofile.close();
}

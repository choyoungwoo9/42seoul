#include "Cure.hpp"


Cure::Cure()
:AMateria("cure")
{

}
Cure::~Cure()
{

}
Cure::Cure(const Cure &param)
:AMateria(param.getType())
{

}
Cure &Cure::operator =(const Cure &param)
{
	this->type = param.getType();
}
AMateria* Cure::clone() const
{
	return(new Cure(*this));
}

void Cure::use(ICharacter &target)
{
	std::cout << "* heals ";
	std::cout << target.getName() << "’s wounds *";
	std::cout << std::endl;
}
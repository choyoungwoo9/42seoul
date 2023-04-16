#include "AMateria.hpp"
#include "ICharacter.hpp"

AMateria::AMateria(std::string const &type)
{
	this->type = type;
}

std::string const &AMateria::getType() const
{
	return this->type;
}

void AMateria::use(ICharacter &target)
{
	if(this->getType() == "ice")
	{
		std::cout << "* shoots an ice bolt at ";
		std::cout << target.getName() << " *";
		std::cout << std::endl;
	}
	if(this->getType() == "cure")
	{
		std::cout << "* heals ";
		std::cout << target.getName() << "’s wounds *";
		std::cout << std::endl;
	}
}

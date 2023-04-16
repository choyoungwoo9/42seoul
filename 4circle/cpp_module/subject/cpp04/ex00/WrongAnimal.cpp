#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal()
:type("undefined")
{
	std::cout << "WrongAnimal:: Default Constructor" << std::endl;
}
WrongAnimal::~WrongAnimal()
{
	std::cout << "WrongAnimal:: Destructor" << std::endl;
}
WrongAnimal::WrongAnimal(const WrongAnimal &param)
{
	std::cout << "WrongAnimal:: copy Constructor" << std::endl;
	*this = param;
}
WrongAnimal &WrongAnimal::operator =(const WrongAnimal &param)
{
	this->type = param.getType();
	return *this;
}
const std::string &WrongAnimal::getType()const
{
	return (this->type);
}

void WrongAnimal::makeSound()const
{
	std::cout << "no type. so, no sound !" << std::endl;
}


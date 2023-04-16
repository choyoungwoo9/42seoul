#include "Dog.hpp"

Dog::Dog()
{
	std::cout << "Dog:: Default Constructor" << std::endl;
	this->type = "Dog";
}
Dog::~Dog()
{
	std::cout << "Dog:: Destructor" << std::endl;
}

Dog::Dog(const Dog &param)
{
	std::cout << "Dog:: Copy Constructor" << std::endl;
	this->type = param.getType();
}
Dog &Dog::operator =(const Dog &param)
{
	this->type = param.getType();
	return *this;
}


void Dog::makeSound()const
{
	std::cout << "wakwakwakwakwakwakwak" << std::endl;
}

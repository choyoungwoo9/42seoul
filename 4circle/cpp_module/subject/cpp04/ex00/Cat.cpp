#include "Cat.hpp"

Cat::Cat()
{
	std::cout << "Cat:: Default Constructor" << std::endl;
	this->type = "Cat";
}
Cat::~Cat()
{
	std::cout << "Cat:: Destructor" << std::endl;
}

Cat::Cat(const Cat &param)
{
	std::cout << "Cat:: Copyt Constructor" << std::endl;
	this->type = param.getType();
}
Cat &Cat::operator =(const Cat &param)
{
	this->type = param.getType();
	return *this;
}

void Cat::makeSound()const
{
	std::cout << "nyaaaaaaaaooooo" << std::endl;
}

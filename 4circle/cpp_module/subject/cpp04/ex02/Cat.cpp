#include "Cat.hpp"

Cat::Cat()
{
	std::cout << "Cat:: Default Constructor" << std::endl;
	this->brain = new Brain();
	this->type = "Cat";
}
Cat::~Cat()
{
	std::cout << "Cat:: Destructor" << std::endl;
	delete brain;
}

Cat::Cat(const Cat &param)
{
	std::cout << "Cat:: Copy Constructor" << std::endl;
	this->type = param.getType();
	this->brain = new Brain(*param.brain);
}

Cat &Cat::operator =(const Cat &param)
{
	this->type = param.getType();
	if(this->brain)
		delete this->brain;
	this->brain = new Brain(*param.brain);
	return *this;
}

void Cat::makeSound()const
{
	std::cout << "nyaaaaaaaaooooo" << std::endl;
}

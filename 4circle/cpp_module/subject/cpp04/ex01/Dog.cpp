#include "Dog.hpp"

Dog::Dog()
{
	std::cout << "Dog:: Default Constructor" << std::endl;
	this->brain = new Brain();
	this->type = "Dog";
}
Dog::~Dog()
{
	std::cout << "Dog:: Destructor" << std::endl;
	if(this->brain)
		delete this->brain;
}

Dog::Dog(const Dog &param)
{
	std::cout << "Dog:: Copy Constructor" << std::endl;
	this->type = param.getType();
	this->brain = new Brain(*param.brain);
}

Dog &Dog::operator =(const Dog &param)
{
	this->type = param.getType();
	if(this->brain)
		delete this->brain;
	this->brain = new Brain(*param.brain);
	return *this;
}

void Dog::makeSound()const
{
	std::cout << "wakwakwakwakwakwakwak" << std::endl;
}

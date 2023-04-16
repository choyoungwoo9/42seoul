#include "Animal.hpp"

Animal::Animal()
:type("undefined")
{
	std::cout << "Animal:: Default Constructor" << std::endl;
}
Animal::~Animal()
{
	std::cout << "Animal:: Destructor" << std::endl;
}
Animal::Animal(const Animal &param)
{
	std::cout << "Animal:: Copy Constructor" << std::endl;
	*this = param;
}
Animal &Animal::operator =(const Animal &param)
{
	this->type = param.getType();
	return *this;
}
const std::string &Animal::getType()const
{
	return (this->type);
}


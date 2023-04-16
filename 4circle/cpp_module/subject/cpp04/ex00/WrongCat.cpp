#include "WrongCat.hpp"

WrongCat::WrongCat()
{
	std::cout << "WrongCat:: Default Constructor" << std::endl;
	this->type = "WrongCat";
}
WrongCat::~WrongCat()
{
	std::cout << "WrongCat:: Destructor" << std::endl;
}

WrongCat::WrongCat(const WrongCat &param)
{
	std::cout << "WrongCat:: Copy Destructor" << std::endl;
	this->type = param.getType();
}
WrongCat &WrongCat::operator =(const WrongCat &param)
{
	this->type = param.getType();
	return *this;
}

void WrongCat::makeSound()const
{
	std::cout << "Wnyaaaaaaaaooooo" << std::endl;
}

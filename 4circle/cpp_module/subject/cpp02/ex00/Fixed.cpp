#include "Fixed.hpp"

int Fixed::getRawBits(void)const
{
	std::cout << "getRawBits member function called" << std::endl;
	return this->rawbit;
}
void Fixed::setRawBits(int const raw)
{
	std::cout << "setRawBits member function called" << std::endl;
	this->rawbit = raw;
}

Fixed::Fixed()
:rawbit(0)
{
	std::cout << "Default constructor called" << std::endl;
}
Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}
Fixed::Fixed(const Fixed& param)
{
	std::cout << "Copy constructor called" << std::endl;
	this->rawbit = param.getRawBits();
}
Fixed& Fixed::operator=(const Fixed& param)
{
	std::cout << "Copy assignment operator called" << std::endl;
	this->rawbit = param.getRawBits();
	return *this;
}

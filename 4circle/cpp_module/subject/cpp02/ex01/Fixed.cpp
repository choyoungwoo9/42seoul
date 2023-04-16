#include "Fixed.hpp"

std::ostream &operator<<(std::ostream &out, const Fixed &ref)
{
    out << ref.toFloat();
    return (out);
}

int Fixed::getRawBits(void)const
{
	return this->rawbit;
}

void Fixed::setRawBits(int const raw)
{
	this->rawbit = raw;
}

Fixed::Fixed()
:rawbit(0)
{
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const int param)
{
	std::cout << "Int constructor called" << std::endl;
	setRawBits(param << this->f_bit_num);
}

Fixed::Fixed(const float param)
{
	std::cout << "Float constructor called" << std::endl;
	int bit_shift_num = 1;
	for(int i = 0; i < this->f_bit_num; i ++)
		bit_shift_num *= 2;
	setRawBits(roundf(param * bit_shift_num));
}

int Fixed::toInt(void)const
{
	return this->rawbit >> f_bit_num;
}

float Fixed::toFloat(void) const
{
	int bit_shift_num = 1;
	for(int i = 0; i < this->f_bit_num; i ++)
		bit_shift_num *= 2;
	return this->rawbit / (float)bit_shift_num;
}

Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}
Fixed::Fixed(const Fixed& param)
{
	std::cout << "Copy constructor called" << std::endl;
	*this = param;
}
Fixed& Fixed::operator=(const Fixed& param)
{
	std::cout << "Copy assignment operator called" << std::endl;
	setRawBits(param.getRawBits());
	return *this;
}

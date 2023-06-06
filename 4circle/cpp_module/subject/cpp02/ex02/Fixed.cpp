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
}

Fixed::Fixed(const int param)
{
	setRawBits(param << this->f_bit_num);
}

Fixed::Fixed(const float param)
{
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
}
Fixed::Fixed(const Fixed& param)
{
	*this = param;
}
Fixed& Fixed::operator=(const Fixed& param)
{
	setRawBits(param.getRawBits());
	return *this;
}

Fixed Fixed::operator+(const Fixed& param) const
{
	Fixed result(this->toFloat()+param.toFloat());
	return(result);
}
Fixed Fixed::operator-(const Fixed& param) const
{
	Fixed result(this->toFloat()-param.toFloat());
	return(result);
}
Fixed Fixed::operator*(const Fixed& param) const
{
	Fixed result(this->toFloat() * param.toFloat());
	return(result);
}
Fixed Fixed::operator/(const Fixed& param) const
{
	if(!param.getRawBits())
	{
		std::cout << "divided by zero is undefined" << std::endl;
		Fixed result(0);
		return result;
	}
	Fixed result(this->toFloat()/param.toFloat());
	return(result);
}
bool Fixed::operator==(const Fixed& param) const
{
	if(this->getRawBits() == param.getRawBits())
		return 1;
	else
		return 0;
}
bool Fixed::operator!=(const Fixed& param) const
{
	if(this->getRawBits() != param.getRawBits())
		return 1;
	else
		return 0;
}
bool Fixed::operator<(const Fixed& param) const
{
	if(this->getRawBits() < param.getRawBits())
		return 1;
	else
		return 0;
}
bool Fixed::operator>(const Fixed& param) const
{
	if(this->getRawBits() > param.getRawBits())
		return 1;
	else
		return 0;
}
bool Fixed::operator<=(const Fixed& param) const
{
	if(this->getRawBits() <= param.getRawBits())
		return 1;
	else
		return 0;
}
bool Fixed::operator>=(const Fixed& param) const
{
	if(this->getRawBits() >= param.getRawBits())
		return 1;
	else
		return 0;
}
Fixed &Fixed::operator++()
{
	this->setRawBits(getRawBits()+1);
	return (*this);
}
Fixed Fixed::operator++(int)
{
	Fixed temp = *this;
	this->setRawBits(getRawBits()+1);
	return temp;
}

Fixed &Fixed::operator--()
{
	this->setRawBits(getRawBits()-1);
	return (*this);
}
Fixed Fixed::operator--(int)
{
	Fixed temp = *this;
	this->setRawBits(getRawBits()-1);
	return temp;
}

// Fixed &Fixed::max(Fixed& p1, Fixed& p2)
// {
// 	if(p1.getRawBits() > p2.getRawBits())
// 		return p1;
// 	else
// 		return p2;
// }
// Fixed &Fixed::min(Fixed& p1, Fixed& p2)
// {
// 	if(p1.getRawBits() < p2.getRawBits())
// 		return p1;
// 	else
// 		return p2;
// }
const Fixed &Fixed::max(const Fixed& p1, const Fixed& p2)
{
	if(p1.getRawBits() > p2.getRawBits())
		return p1;
	else
		return p2;
}
const Fixed &Fixed::min(const Fixed& p1, const Fixed& p2)
{
	if(p1.getRawBits() < p2.getRawBits())
		return p1;
	else
		return p2;
}

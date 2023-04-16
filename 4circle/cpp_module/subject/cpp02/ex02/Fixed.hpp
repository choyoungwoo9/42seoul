#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <cmath>

class Fixed
{
	public:
		Fixed();
		Fixed(const int param);
		Fixed(const float param);
		~Fixed();
		Fixed(const Fixed& param);
		Fixed& operator=(const Fixed& param);
		int getRawBits(void) const;
		void setRawBits(int const raw);
		float toFloat(void) const;
		int toInt(void)const;

		Fixed operator+(const Fixed& param) const;
		Fixed operator-(const Fixed& param) const;
		Fixed operator*(const Fixed& param) const;
		Fixed operator/(const Fixed& param) const;
		bool operator==(const Fixed& param) const;
		bool operator!=(const Fixed& param) const;
		bool operator<(const Fixed& param) const;
		bool operator>(const Fixed& param) const;
		bool operator<=(const Fixed& param) const;
		bool operator>=(const Fixed& param) const;
		Fixed &operator++();
		Fixed operator++(int);
		Fixed &operator--();
		Fixed operator--(int);
		static Fixed &max(Fixed& p1, Fixed& p2);
		static Fixed &min(Fixed& p1, Fixed& p2);
		static const Fixed &max(const Fixed& p1, const Fixed& p2);
		static const Fixed &min(const Fixed& p1, const Fixed& p2);
	private:
		static const int f_bit_num = 8;
		int rawbit;
};

std::ostream &operator<<(std::ostream &out, const Fixed &ref);

#endif

#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed
{
	public:
		Fixed();
		~Fixed();
		Fixed(const Fixed& param);
		Fixed& operator=(const Fixed& param);
		int getRawBits(void) const;
		void setRawBits(int const raw);

	private:
		static const int f_bit_num = 8;
		int rawbit;
};

#endif
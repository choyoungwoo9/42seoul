#include <iostream>
#include "Fixed.hpp"

int main( void ) 
{ 
	Fixed a;
	Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) );
	std::cout << a << std::endl;
	std::cout << ++a << std::endl;
	std::cout << a << std::endl;
	std::cout << a++ << std::endl;
	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << Fixed::max( a, b ) << std::endl;

	// Fixed c(20.3f);
	// Fixed d(30.4f);
	// std::cout << " 20.3 + 30.4 : " << c+d << std::endl;
	// std::cout << " 20.3 - 30.4 : " << c-d << std::endl;
	// std::cout << " 20.3 * 30.4 : " << c*d << std::endl;
	// std::cout << " 20.3 / 30.4 : " << c/d << std::endl;
	// std::cout << " 20.3 == 30.4 : " << (int)(c==d) << std::endl;
	// std::cout << " 20.3 != 30.4 : " << (int)(c!=d) << std::endl;
	// std::cout << " 20.3 < 30.4 : " << (int)(c<d) << std::endl;
	// std::cout << " 20.3 > 30.4 : " << (int)(c>d) << std::endl;
	// std::cout << " 20.3 <= 30.4 : " << (int)(c<=d) << std::endl;
	// std::cout << " 20.3 >= 30.4 : " << (int)(c>=d) << std::endl;
	return 0;
}

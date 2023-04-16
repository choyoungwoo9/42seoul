#ifndef ICE_HPP
#define ICE_HPP

#include "AMateria.hpp"

class Ice : AMateria
{
	public:
		Ice();
		~Ice();
		Ice(const Ice &param);
		Ice &operator =(const Ice &param);
		AMateria* clone() const;
		virtual void use();
};

#endif
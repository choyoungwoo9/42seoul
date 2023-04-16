#ifndef CURE_HPP
#define CURE_HPP

#include "AMateria.hpp"

class Cure : AMateria
{
	public:
		Cure();
		~Cure();
		Cure(const Cure &param);
		Cure &operator =(const Cure &param);
		AMateria* clone() const;
		virtual void use(ICharacter &target);
};

#endif
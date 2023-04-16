#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "ICharacter.hpp"
#include "AMateria.hpp"

class Character : ICharacter
{
	public:
		Character();
		Character(std::string &param);
		Character(const Character &param);
		Character &operator =(const Character &param);
		virtual ~Character();
		virtual std::string const &getName()const;
		virtual void equip(AMateria *m);
		virtual void unequip(int idx);
		virtual void use(int idx, ICharacter& target);
	private:
		AMateria *slot[4];
		std::string name;
};

#endif
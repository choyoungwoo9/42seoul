#ifndef HUMANB_HPP
#define HUMANB_HPP

#include "Weapon.hpp"
#include <iostream>

class HumanB
{
	public:
		HumanB(const std::string &p_name);
		void setWeapon(Weapon &p_weapon);
		void attack(void)const;
	private:
		std::string name;
		Weapon *my_weapon;
};


#endif
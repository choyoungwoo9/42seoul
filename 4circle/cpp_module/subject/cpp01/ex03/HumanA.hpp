#ifndef HUMANA_HPP
#define HUMANA_HPP

#include "Weapon.hpp"
#include <iostream>

class HumanA
{
	public:
		HumanA(const std::string &p_name, Weapon &p_weapon);
		void attack(void)const;
	private:
		std::string name;
		Weapon &my_weapon;
};

#endif
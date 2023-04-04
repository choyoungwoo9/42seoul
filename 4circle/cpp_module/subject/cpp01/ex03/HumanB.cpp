#include "HumanB.hpp"

HumanB::HumanB(const std::string &p_name)
:name(p_name), my_weapon(NULL)
{}

void HumanB::attack(void)const
{
	if(!my_weapon)
		std::cout << this->name << " attacks with their " << "hands ... " << std::endl;
	else
		std::cout << this->name << " attacks with their " << my_weapon->getType() << std::endl;
}

void HumanB::setWeapon(Weapon &p_weapon)
{
	this->my_weapon = &p_weapon;
}
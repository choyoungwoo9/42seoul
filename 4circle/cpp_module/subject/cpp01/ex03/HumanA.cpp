#include "HumanA.hpp"

HumanA::HumanA(const std::string &p_name, Weapon &p_weapon)
:name(p_name), my_weapon(p_weapon)
{}

void HumanA::attack(void)const
{
	std::cout << this->name << " attacks with their " << my_weapon.getType() << std::endl;
}

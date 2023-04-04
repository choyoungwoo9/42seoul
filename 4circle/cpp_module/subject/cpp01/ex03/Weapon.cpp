#include "Weapon.hpp"

Weapon::Weapon(const std::string &param)
:type(param)
{}

const std::string &Weapon::getType()const
{
	return this->type;
}

void Weapon::setType(std::string const &param)
{
	this->type = param;
}

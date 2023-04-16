#include "FragTrap.hpp"

FragTrap::FragTrap(const std::string &param)
{
	std::cout << "Frag:: param constructor" << std::endl;
	name = param;
	Hit_points = 100;
	Energy_point = 100;
	Attack_damage = 30;
}

FragTrap::FragTrap()
{
	std::cout << "Frag:: default constructor" << std::endl;
	name = "youngwch";
	Hit_points = 100;
	Energy_point = 100;
	Attack_damage = 30;
}

FragTrap::~FragTrap()
{
	std::cout << "Frag:: dest" << std::endl;
}

FragTrap::FragTrap(const FragTrap &param)
{
	std::cout << "Frag:: copy " << std::endl;
	*this = param;
}

FragTrap &FragTrap::operator =(const FragTrap &param)
{
	std::cout << "Frag::assign operator" << std::endl;
	this->name = param.name;
	this->Hit_points = param.Hit_points;
	this->Energy_point = param.Energy_point;
	this->Attack_damage = param.Attack_damage;
	return *this;
}

void FragTrap::attack(const std::string& param)
{
	if(this->Hit_points <= 0)
	{
		std::cout << this->name << " Frag:: dead_state..." << std::endl;
		return ;
	}
	if(this->Energy_point <= 0)
	{
		std::cout << this->name << " Frag:: no energy" << std::endl;
		return ;
	}
	std::cout << "Frag:: " << this->name << " attacks " << param
		<< ", causing " << this->Attack_damage <<  " points of damage!" << std::endl;
	this->Energy_point --;
}

void FragTrap::highFivesGuys(void)
{
	std::cout << "Frag::HIGHFIVE !!!" << std::endl;
}
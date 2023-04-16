#include "ScavTrap.hpp"

ScavTrap::ScavTrap(const std::string &param)
{
	std::cout << "Scav:: param constructor" << std::endl;
	name = param;
	Hit_points = 100;
	Energy_point = 50;
	Attack_damage = 20;
}

ScavTrap::ScavTrap()
{
	std::cout << "Scav:: default constructor" << std::endl;
	name = "youngwch";
	Hit_points = 100;
	Energy_point = 50;
	Attack_damage = 20;
}

ScavTrap::~ScavTrap()
{
	std::cout << "Scav:: dest" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap &param)
{
	std::cout << "Scav:: copy " << std::endl;
	*this = param;
}

ScavTrap &ScavTrap::operator =(const ScavTrap &param)
{
	std::cout << "Scav::assign operator" << std::endl;
	this->name = param.name;
	this->Hit_points = param.Hit_points;
	this->Energy_point = param.Energy_point;
	this->Attack_damage = param.Attack_damage;
	return *this;
}

void ScavTrap::guardGate()
{
	std::cout << "Scav::i am guardGate " << std::endl;
}

void ScavTrap::attack(const std::string& param)
{
	if(this->Hit_points <= 0)
	{
		std::cout << this->name << " Scav:: dead_state..." << std::endl;
		return ;
	}
	if(this->Energy_point <= 0)
	{
		std::cout << this->name << " Scav:: no energy" << std::endl;
		return ;
	}
	std::cout << "Scav:: " << this->name << " attacks " << param
		<< ", causing " << this->Attack_damage <<  " points of damage!" << std::endl;
	this->Energy_point --;
}

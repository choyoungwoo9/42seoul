#include "ClapTrap.hpp"

ClapTrap::ClapTrap(const std::string &param)
:Hit_points(10), Energy_point(10), Attack_damage(0)
{
	std::cout << "Clap::param Constructor" << std::endl;
	this->name = param;
}

ClapTrap::ClapTrap()
:name("youngwch"), Hit_points(10), Energy_point(10), Attack_damage(0)
{
	std::cout << "Clap::Default Constructor" << std::endl;
}

ClapTrap::~ClapTrap()
{
	std::cout << "Clap::Destructor" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &param)
{
	std::cout << "Clap::copy" << std::endl;
	this->name = param.name;
	this->Hit_points = param.Hit_points;
	this->Energy_point = param.Energy_point;
	this->Attack_damage = param.Attack_damage;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &param)
{
	std::cout << "Clap::assign operator" << std::endl;
	this->name = param.name;
	this->Hit_points = param.Hit_points;
	this->Energy_point = param.Energy_point;
	this->Attack_damage = param.Attack_damage;
	return *this;
}

void ClapTrap::attack(const std::string& param)
{
	if(this->Hit_points <= 0)
	{
		std::cout << "Clap:: " << this->name << " dead_state..." << std::endl;
		return ;
	}
	if(this->Energy_point <= 0)
	{
		std::cout << "Clap:: " << this->name << " no energy" << std::endl;
		return ;
	}
	std::cout << "Clap:: " << this->name << " attacks " << param
		<< ", causing " << this->Attack_damage <<  " points of damage!" << std::endl;
	this->Energy_point --;
}

void ClapTrap::takeDamage(unsigned int amount)
{
	if(this->Hit_points <= 0)
	{
		std::cout << "Clap:: " << this->name << " dead state..." << std::endl;
		return ;
	}
	std::cout << "Clap:: " << this->name << " take Damage " << amount << std::endl;
	this->Hit_points -= amount;
	if(this->Hit_points <= 0)
		std::cout << "Clap:: " << this->name << " now dead..." << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount)
{
	if(this->Hit_points <= 0)
	{
		std::cout << "Clap:: " << this->name << " dead_state..." << std::endl;
		return ;
	}
	if(this->Energy_point <= 0)
	{
		std::cout << "Clap:: " << this->name << " no energy" << std::endl;
		return ;
	}
	std::cout << "Clap:: " << this->name << " repair " << amount << "..." <<std::endl;
	this->Hit_points += amount;
	this->Energy_point --;
}

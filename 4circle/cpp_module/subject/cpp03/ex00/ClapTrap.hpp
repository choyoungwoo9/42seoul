#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <string>
#include <iostream>

class ClapTrap
{
	public:
		ClapTrap(const std::string &param);
		ClapTrap();
		~ClapTrap();
		ClapTrap(const ClapTrap &param);
		ClapTrap &operator =(const ClapTrap &param);
		void attack(const std::string& target);
		void takeDamage(unsigned int amount);
		void beRepaired(unsigned int amount);

	private:
		std::string	name;
		int Hit_points;
		int Energy_point;
		int Attack_damage;
};

#endif
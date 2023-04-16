#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap
{
	public:
		ScavTrap(const std::string &param);
		ScavTrap();
		~ScavTrap();
		ScavTrap(const ScavTrap &param);
		ScavTrap &operator =(const ScavTrap &param);
		void attack(const std::string& target);
		void guardGate();
};

#endif
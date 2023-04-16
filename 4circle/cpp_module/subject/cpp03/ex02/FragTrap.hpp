#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP

#include "ClapTrap.hpp"

class FragTrap : public ClapTrap
{
	public:
		FragTrap(const std::string &param);
		FragTrap();
		~FragTrap();
		FragTrap(const FragTrap &param);
		FragTrap &operator =(const FragTrap &param);
		void attack(const std::string& target);
		void highFivesGuys(void);
};

#endif
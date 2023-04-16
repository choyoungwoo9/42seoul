#include "Zombie.hpp"

Zombie::Zombie()
{
	
}

void Zombie::announce(void) const
{
	std::cout << this->name <<" : BraiiiiiiinnnzzzZ..." << std::endl;
}

void Zombie::set_name(std::string const &param)
{
	this->name = param;
}
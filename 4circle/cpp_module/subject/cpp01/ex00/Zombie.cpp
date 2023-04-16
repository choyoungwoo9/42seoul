#include "Zombie.hpp"

Zombie::Zombie(std::string const &param)
{
	this->name = param;
}

void Zombie::announce(void) const
{
	std::cout << this->name <<" : BraiiiiiiinnnzzzZ..." << std::endl;
}

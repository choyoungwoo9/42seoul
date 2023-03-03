#include "Zombie.h"

void Zombie::announce()
{
    std::cout << this->get_name() << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

Zombie::Zombie(std::string name)
{
    this->set_name(name);
}

Zombie::~Zombie()
{
    std::cout << this->get_name() << "   destruct" << std::endl;
}

std::string Zombie::get_name()
{
    return this->_name;
}
void Zombie::set_name(std::string name)
{
    this->_name = name;
}
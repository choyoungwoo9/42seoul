#include "Zombie.h"

void Zombie::announce()
{
    std::cout << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

void Zombie::set_name(std::string name)
{
    _name = name;
}

Zombie::Zombie()
{
}
Zombie::~Zombie()
{
}

Zombie *zombieHorde(int N, std::string name)
{
    Zombie *zombie_ar = new Zombie[N];
    for(int i = 0; i < N; i ++)
        zombie_ar[i].set_name(name);
    return zombie_ar;
}

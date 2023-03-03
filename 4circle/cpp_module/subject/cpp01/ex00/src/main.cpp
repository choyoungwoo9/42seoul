#include <iostream>
#include "Zombie.h"

int main()
{
    Zombie *zombie = new Zombie("new_zombie");
    zombie->announce();
    Zombie *zombie2 = newZombie("my_new_Zombie");
    zombie2->announce();
    for(int i = 0; i < 1; i ++)
    {
        Zombie zombie3("stack_zombie");
        zombie3.announce();
    }
    randomChump("in_stack_zombie");
    delete zombie;
    delete zombie2;
}

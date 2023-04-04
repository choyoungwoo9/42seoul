#include "Zombie.hpp"

void check_leak()
{
    Zombie *ptr = zombieHorde(10, "youngwch");
    for(int i = 0; i < 10; i ++)
    {
        ptr[i].announce();
    }
    delete[] ptr;
}

int main()
{
    check_leak();
}

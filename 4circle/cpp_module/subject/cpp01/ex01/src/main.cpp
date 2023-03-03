#include "Zombie.h"

int main()
{
    int N = 4;
    Zombie *zombie_ar = zombieHorde(N, "youngwoo");
    for(int i = 0; i < N; i ++)
        zombie_ar[i].announce();
    delete[] zombie_ar;
}

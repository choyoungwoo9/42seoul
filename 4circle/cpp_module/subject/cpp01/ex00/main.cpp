#include "Zombie.hpp"

Zombie *is_heap()
{
	return newZombie("heapzombie");
}

int main()
{
	Zombie *heapZombie = is_heap();
	randomChump("stack Chump");
	heapZombie->announce();
	delete heapZombie;
}
#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <string>
#include <iostream>

class Zombie
{
	public:
		Zombie(std::string const &param);
		void announce(void) const;

	private:
		std::string name;
};

Zombie *newZombie(std::string name);
void randomChump(std::string name);
#endif
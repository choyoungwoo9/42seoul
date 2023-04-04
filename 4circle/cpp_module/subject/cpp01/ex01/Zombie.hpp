#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <string>
#include <iostream>

class Zombie
{
	public:
		Zombie()
		{}
		void set_name(std::string const &param);
		void announce(void) const;

	private:
		std::string name;
};

Zombie *zombieHorde(int N, std::string name);

#endif

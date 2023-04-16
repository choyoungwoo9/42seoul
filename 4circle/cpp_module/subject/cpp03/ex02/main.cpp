#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main()
{
	ClapTrap clap("clap");
	clap.attack("enemy");
	ScavTrap scav("scav");
	scav.attack("enemy");
	scav.guardGate();
	FragTrap frag("frag");
	frag.attack("enemy");
	frag.highFivesGuys();
}
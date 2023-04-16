#include "ClapTrap.hpp"

int main()
{
	ClapTrap A("youngwoo");
	ClapTrap B("jinwoo");
	A.attack("BB");
	A.takeDamage(9);
	B=A;
	B.takeDamage(1);
	A.takeDamage(1);

	B.takeDamage(3);

	ClapTrap C("sowoo");
	C.attack("hey");
	C.attack("hey");
	C.attack("hey");
	C.attack("hey");
	C.attack("hey");
	C.attack("hey");
	C.attack("hey");
	C.attack("hey");
	C.attack("hey");
	C.attack("hey");
	C.attack("hey");

	ClapTrap D;
	D.beRepaired(100);
	D.takeDamage(109);
	D.takeDamage(1);
	D.beRepaired(20);
}

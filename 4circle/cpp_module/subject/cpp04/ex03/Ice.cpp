#include "Ice.hpp"

class Ice : AMateria
{
	public:
		Ice();
		~Ice();
		Ice(const Ice &param);
		Ice &operator =(const Ice &param);
		AMateria* clone() const;
		virtual void use();
};

Ice::Ice()
:AMateria("Ice")
{

}
Ice::~Ice()
{

}
Ice::Ice(const Ice &param)
:AMateria(param.getType())
{

}
Ice &Ice::operator =(const Ice &param)
{
	this->type = param.getType();
}
AMateria* Ice::clone() const
{
	return(new Ice(*this));
}

void Ice::use(ICharacter &target)
{
	std::cout << "* shoots an ice bolt at ";
	std::cout << target.getName() << " *";
	std::cout << std::endl;
}

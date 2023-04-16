#ifndef METERIASOURCE_HPP
#define METERIASOURCE_HPP

#include "IMeteriaSource.hpp"
#include "Cure.hpp"

class MateriaSource : IMateriaSource
{
	public:
	virtual ~MateriaSource();
	void learnMateria(AMateria*);
	AMateria* createMateria(std::string const & type);

	private:
		AMateria *slot[4];
};

MateriaSource::~MateriaSource()
{

}
void MateriaSource::learnMateria(AMateria* param)
{

}
// AMateria* MateriaSource::createMateria(std::string const & type)
// {
// 	if(type == "cure")
// 	{
// 		AMateria *ret = new Cure();
// 		return ret;
// 	}
// 	if(type == "ice")
// 	{
// 		AMateria *ret = new Ice();
// 		return ret;
// 	}
// 	else
// 	{
// 		return 0;
// 	}
// }

#endif
#include "Character.hpp"


Character::Character()
{
	for(int i = 0; i < 4; i ++)
		this->slot[i] = NULL;
}

Character::Character(std::string &param)
:Character()
{
	this->name = param;
}

Character::Character(const Character &param)
{
	*this = param;
}
Character &Character::operator =(const Character &param)
{
	this->name = param.getName();
	for(int i = 0; i < 4; i ++)
	{
		if(this->slot[i])
			delete this->slot[i];
		this->slot[i] = NULL;
	}
	for(int i = 0; i < 4; i ++)
	{
		if(param.slot[i])
			this->slot[i] = param.slot[i]->clone();
	}
	return *this;
}

Character::~Character()
{
	for(int i = 0; i < 4; i ++)
	{
		if(!this->slot[i])
			break;
		delete this->slot[i];
	}
}
std::string const &Character::getName()const
{
	return this->name;
}

void Character::equip(AMateria *m)
{
	if(!m)
		return ;
	for(int i = 0; i < 4; i ++)
	{
		if(!slot[i])
		{
			slot[i] = m;
			return ;
		}
	}
	delete m;
}
void Character::unequip(int idx)
{
	for(int i = 3; i >= 0; i --)
	{
		if(slot[i])
		{
			delete slot[i];
			slot[i] = NULL;
			return ;
		}
	}
}
void Character::use(int idx, ICharacter& target)
{
	if(!slot[idx])
		return;
	slot[idx]->use(target);
}

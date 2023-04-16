#include "Brain.hpp"

Brain::Brain()
{
	std::cout << "Brain:: Default Constructor" << std::endl;
}

Brain::~Brain()
{
	std::cout << "Brain:: Destructor" << std::endl;
}

Brain::Brain(const Brain &param)
{
	std::cout << "Brain:: Copy Constructor" << std::endl;
	*this = param;
}

Brain &Brain::operator =(const Brain &param)
{
	for(int i = 0; i < 100; i ++)
		this->ideas[i] = param.ideas[i];
	return *this;
}
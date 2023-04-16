#ifndef DOG_HPP
#define DOG_HPP

#include "Animal.hpp"

class Dog : public Animal
{
	public:
		Dog();
		virtual ~Dog();
		Dog(const Dog &param);
		Dog &operator =(const Dog &param);
		virtual void makeSound()const;
};

#endif
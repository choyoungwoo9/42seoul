#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <string>
#include <iostream>

class Animal
{
	public:
		Animal();
		virtual ~Animal();
		Animal(const Animal &param);
		Animal &operator =(const Animal &param);
		const std::string &getType()const;
		virtual void makeSound()const = 0;

	protected:
		std::string type;
};

#endif

#ifndef WRONG_ANIMAL_HPP
#define WRONG_ANIMAL_HPP

#include <string>
#include <iostream>

class WrongAnimal
{
	public:
		WrongAnimal();
		~WrongAnimal();
		WrongAnimal(const WrongAnimal &param);
		WrongAnimal &operator =(const WrongAnimal &param);
		const std::string &getType()const;
		void makeSound()const;

	protected:
		std::string type;
};

#endif

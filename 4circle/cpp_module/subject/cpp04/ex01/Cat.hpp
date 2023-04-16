#ifndef CAT_HPP
#define CAT_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal
{
	public:
		Cat();
		virtual ~Cat();
		Cat(const Cat &param);
		Cat &operator =(const Cat &param);
		virtual void makeSound()const;
	private:
		Brain *brain;
};
#endif
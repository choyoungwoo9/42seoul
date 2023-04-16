#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"

int main() 
{
	const Animal* j = new Dog(); 
	const Animal* i = new Cat();
	delete j;//should not create a leak
	delete i;
	
	Animal *ar[100];
	for(int x = 0; x < 50; x ++)
	{
		ar[x] = new Dog();
	}
	for(int x = 50; x < 100; x ++)
	{
		ar[x] = new Cat();
	}
	for(int x = 0; x < 100; x ++)
	{
		ar[x]->makeSound();
	}
	for(int x = 0; x < 100; x ++)
	{
		delete ar[x];
	}

	std::cout << "new test" << std::endl;
	Cat *obj1 = new Cat();
	Cat *obj2 = new Cat();
	obj1 = obj2;

	Cat *obj3 = new Cat();
	Cat *obj4 = new Cat(*obj3);
	obj4->makeSound();

	//system("leaks fire");
}
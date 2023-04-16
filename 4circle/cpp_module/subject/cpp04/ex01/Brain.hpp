#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <string>
#include <iostream>

class Brain
{
	private:
		std::string ideas[100];
	
	public:
		Brain();
		~Brain();
		Brain(const Brain &param);
		Brain &operator =(const Brain &param);
};

#endif
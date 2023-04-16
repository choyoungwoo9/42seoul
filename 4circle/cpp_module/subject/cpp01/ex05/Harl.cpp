#include "Harl.hpp"

void Harl::complain(std::string level)
{
	void (Harl::*func1)() = NULL;
	if(level == "DEBUG")
		func1 = &Harl::debug;
	if(level == "INFO")
		func1 = &Harl::info;
	if(level == "WARNING")
		func1 = &Harl::warning;
	if(level == "ERROR")
		func1 = &Harl::error;
	if(func1)
		(this->*func1)();
}

void Harl::debug()
{
	std::cout << "DEBUG : " << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-special- ketchup burger. I really do!" << std::endl;
}

void Harl::info()
{
	std::cout << "INFO : " << "I cannot believe adding extra bacon costs more money. You didn’t put enough bacon in my burger! If you did, I wouldn’t be asking for more!" << std::endl;
}
void Harl::warning()
{
	std::cout << "WARNING : " << "I think I deserve to have some extra bacon for free. I’ve been coming for years whereas you started working here since last month." << std::endl;
}
void Harl::error()
{
	std::cout << "ERROR : " << "This is unacceptable! I want to speak to the manager now." << std::endl;
}
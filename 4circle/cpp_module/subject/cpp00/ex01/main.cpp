#include "PhoneBook.hpp"
#include <string>
#include <iostream>

PhoneBook book;

int main()
{
	while(1)
	{
		std::string order;
		std::cout << "ADD or SEARCH or EXIT  <-- choice your order. " << std::endl;
		std::getline(std::cin, order);
		if(order == "ADD")
			book.add_contact();
		else if(order == "SEARCH")
			book.search_contact();
		else if(order == "EXIT")
			break;
		if (std::cin.eof()==1) 
		{
			std::cout << "eof end" << std::endl;
			break;
		}
	}
}

#include "PhoneBook.hpp"

void PhoneBook::add_contact()
{
	contact_ar[this->index].set_first_name(get_input("write first_name"));
	contact_ar[this->index].set_last_name(get_input("write last_name"));
	contact_ar[this->index].set_number(get_input("write number"));
	contact_ar[this->index].set_nickname(get_input("write nickname"));
	contact_ar[this->index].set_darkest_secret(get_input("write darkest_secret"));
	this->index = (this->index + 1) % 8;
	if(size < 8)
		size ++;
}

void PhoneBook::search_contact()
{
	print_all_contact();
	std::string const &input_index = get_input("please choose index num");
	if(is_valid_index(input_index))
	{
		print_detail(input_index[0]-'0');
	}
	else
	{
		std::cout << "invalid index" <<std:: endl;
	}
}



int PhoneBook::is_valid_index(std::string const &input)
{
	if(input.size() != 1)
		return 0;
	if(input[0] - '0' >= this->size || input[0] - '0' < 0)
		return 0;
	return 1;
}

std::string PhoneBook::get_input(std::string mention)
{
	std::string input;
	while(input.empty())
	{
		std::cout << mention << std::endl;
		std::getline(std::cin, input);
		if (std::cin.eof()==1) 
		{
			std::cout << "eof end" << std::endl;
			exit(0);
			break;
		}
	}
	return input;
}

void PhoneBook::print_all_contact()
{
	for(int i = 0; i < 8 && i < this->size; i ++)
	{
		std::cout << "|";
		print_rough_str(std::to_string(i));
		std::cout << "|";
		print_rough_str(contact_ar[i].get_first_name());
		std::cout << "|";
		print_rough_str(contact_ar[i].get_last_name());
		std::cout << "|";
		print_rough_str(contact_ar[i].get_nickname());
		std::cout << "|" << std::endl;		
	}
}

void PhoneBook::print_rough_str(std::string const &str)
{
	for(int i = str.size(); i < 10; i ++)
	{
		std::cout << ' ';
	}
	for(int i = 0; i < str.size()-1 && i < 9; i ++)
	{
		std::cout << str[i];
	}
	if(str.size() > 10)
		std::cout << '.';
	else
		std::cout << str[str.size()-1];
}

void PhoneBook::print_detail(int cur_index)
{
	std::cout << contact_ar[cur_index].get_first_name() << std::endl;
	std::cout << contact_ar[cur_index].get_last_name() << std::endl;
	std::cout << contact_ar[cur_index].get_nickname() << std::endl;
	std::cout << contact_ar[cur_index].get_number() << std::endl;
	std::cout << contact_ar[cur_index].get_darkest_secret() << std::endl;
}
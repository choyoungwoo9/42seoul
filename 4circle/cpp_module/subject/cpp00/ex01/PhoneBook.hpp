#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"
#include <iostream>
#include <string>

class PhoneBook
{
	public:
			PhoneBook()
			:index(0), size(0)
			{}
		void add_contact();
		void search_contact();
	private:
		void print_all_contact();
		void print_detail(int cur_index);
		void print_rough_str(std::string const &str);
		std::string get_input(std::string mention);
		int is_valid_index(std::string const &input);
		Contact contact_ar[8];
		int index;
		int size;
};

#endif

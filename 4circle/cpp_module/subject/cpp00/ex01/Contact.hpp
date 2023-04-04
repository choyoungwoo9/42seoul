#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <string>
#include <iostream>

class Contact
{
	public:
		std::string &get_first_name();
		std::string &get_last_name();
		std::string &get_nickname();
		std::string &get_number();
		std::string &get_darkest_secret();
		void set_first_name(std::string const &param);
		void set_last_name(std::string const &param);
		void set_nickname(std::string const &param);
		void set_number(std::string const &param);
		void set_darkest_secret(std::string const &param);
	private:
		std::string first_Name;
		std::string last_name;
		std::string nickname;
		std::string number;
		std::string darkest_secret;
};

#endif
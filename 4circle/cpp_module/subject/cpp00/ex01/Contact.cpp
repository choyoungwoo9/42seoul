#include "Contact.hpp"

std::string &Contact::get_first_name()
{
	return this->first_Name;
}

std::string &Contact::get_last_name()
{
	return this->last_name;
}
std::string &Contact::get_nickname()
{
	return this->nickname;
}
std::string &Contact::get_number()
{
	return this->number;
}
std::string &Contact::get_darkest_secret()
{
	return this->darkest_secret;
}

void Contact::set_first_name(std::string const &param)
{
	this->first_Name = param;
}

void Contact::set_last_name(std::string const &param)
{
	this->last_name = param;
}

void Contact::set_nickname(std::string const &param)
{
	this->nickname = param;
}

void Contact::set_number(std::string const &param)
{
	this->number = param;
}

void Contact::set_darkest_secret(std::string const &param)
{
	this->darkest_secret = param;
}

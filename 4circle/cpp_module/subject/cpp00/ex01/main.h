#ifndef MAIN_H
#define MAIN_H

#include <iostream>

class Contact
{
public:
    Contact()
    {
    }
    void set_member(std::string first_name, std::string last_name,std::string nickname,std::string phone_number, std::string darkest_secret);
    void print_member_simple(int index);
    void print_column_simple(std::string str);
    void print_member_all();
private:
    std::string _first_name;
    std::string _last_name;
    std::string _nickname;
    std::string _phone_number;
    std::string _darkest_secret;
};

void Contact::set_member(std::string first_name, std::string last_name,std::string nickname,std::string phone_number, std::string darkest_secret)
{
    this->_first_name = first_name;
    this->_last_name = last_name;
    this->_nickname = nickname;
    this->_phone_number = phone_number;
    this->_darkest_secret = darkest_secret;
}

void Contact::print_column_simple(std::string str)
{
    if(str.size() > 10)
    {
        for(int i = 0; i < 9; i++)
            std::cout << str[i];
        std::cout << '.';
    }
    else
    {
        for(int i = 0; i < 10; i ++)
        {
            if(str.size() + i < 10)
                std::cout << ' ';
            else
                std::cout << str[str.size()+i-10];
        }
    }
}

void Contact::print_member_simple(int index)
{
    std::cout << "|         " << index << '|';
    print_column_simple(_first_name);
    std::cout << '|';
    print_column_simple(_last_name);
    std::cout << '|';
    print_column_simple(_nickname);
    std::cout << '|' << std::endl;
}

void Contact::print_member_all()
{
    std::cout << _first_name << std::endl;
    std::cout << _last_name << std::endl;
    std::cout << _nickname << std::endl;
    std::cout << _phone_number << std::endl;
    std::cout << _darkest_secret << std::endl;
}

class PhoneBook {
public:
    PhoneBook()
    {
        _index = 0;
        _count = 0;
    }
    void add_phone_book();
    void search_phone_book();
private:
    Contact contact_ar[8];
    int _index;
    int _count;
};

void PhoneBook::add_phone_book()
{
    std::string first_name;
    std::string last_name;
    std::string nickname;
    std::string phone_number;
    std::string darkest_secret;
    std::cout << "write first name" << std::endl;
    std::cin >> first_name;
    std::cout << "write last name" << std::endl;
    std::cin >> last_name;
    std::cout << "write nickname" << std::endl;
    std::cin >> nickname;
    std::cout << "write phone number" << std::endl;
    std::cin >> phone_number;
    std::cout << "write darkest secret" << std::endl;
    std::cin >> darkest_secret;
    if(_count < 8)
    _count ++;
    contact_ar[_index].set_member(first_name, last_name, nickname, phone_number, darkest_secret);
    _index = (_index + 1) % 8;
}

void PhoneBook::search_phone_book()
{
    for(int i = 0; i < _count; i ++)
        contact_ar[i].print_member_simple(i);
    int index;
    while(1)
    {
        //int index;
        std::cout << "what do you want to see? (write index)" << std::endl;
        std::cin >> index;
        if(index >= 0 && index < _count)
            break;
        if(std::cin.fail())
        {
            std::cout << "wrong input" << std::endl;
            std::cin.clear();
            std::cin.ignore(2147483647, '\n');
        }
        else
            std::cout << "wrong index" << std::endl;
    }
    contact_ar[index].print_member_all();
}
#endif

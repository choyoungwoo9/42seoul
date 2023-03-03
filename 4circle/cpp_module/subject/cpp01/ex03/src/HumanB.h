//
// Created by Youngwoo Cho on 3/1/23.
//

#ifndef CPP01_HUMANB_H
#define CPP01_HUMANB_H

#include "Weapon.h"

class HumanB {
private:
    Weapon *weapon;
    std::string _name;
public:
    HumanB(std::string name);
    void attack();
    void set_weapon();
    std::string &get_weapon_name();
};

HumanB::HumanB(std::string name)
{
    _name = name;
    weapon = nullptr;
}

HumanB::attack()
{
//    cout << _name << " attacks with their " <<
}

HumanB::std::string &get_weapon_name()
{

}
#endif //CPP01_HUMANB_H

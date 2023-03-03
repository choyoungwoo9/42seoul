//
// Created by Youngwoo Cho on 3/1/23.
//

#ifndef CPP01_HUMANA_H
#define CPP01_HUMANA_H
#include "Weapon.h"

class HumanA {
private:
    Weapon *_weapon;
    std::string _name;
public:
    HumanA(std::string name, Weapon weapon);
    ~HumanA();
    void attack();
};

HumanA::HumanA(std::string name, Weapon weapon)
{
    _name = name;
    _weapon = new Weapon(weapon);
}

HumanA::~HumanA()
{
    delete _weapon;
}

HumanA::attack()
{
    cout << _name << " attacks with their " << _weapon->getType() << endl;
}

#endif

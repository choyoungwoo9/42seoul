//
// Created by Youngwoo Cho on 3/1/23.
//

#include "Weapon.h"
void Weapon::setType(std::string p_type)
{
    type = p_type;
}

std::string& Weapon::getType()
{
    return type;
}

Weapon::Weapon(std::string p_type)
{
    setType(p_type);
}
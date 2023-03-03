#ifndef CPP01_WEAPON_H
#define CPP01_WEAPON_H

#include <string>
#include <iostream>

class Weapon {
private:
    std::string type;
public:
    const std::string& getType();
    void setType(std::string p_type);
    Weapon(std::string p_type);
};

#endif
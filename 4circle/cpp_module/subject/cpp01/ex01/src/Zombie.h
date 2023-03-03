#ifndef CPP01_ZOMBIE_H
#define CPP01_ZOMBIE_H

#include <string>
#include <iostream>
class Zombie
{
private:
    std::string _name;
public:
    void announce();
    void set_name(std::string name);
    Zombie();
    Zombie(std::string name);
    ~Zombie();
};

Zombie *zombieHorde(int N, std::string name);

#endif

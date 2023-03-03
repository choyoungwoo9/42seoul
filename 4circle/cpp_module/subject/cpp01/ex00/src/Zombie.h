#ifndef CPP01_ZOMBIE_H
#define CPP01_ZOMBIE_H

#include <iostream>

class Zombie
{
private:
    std::string _name;

public:
    void announce();
    std::string get_name();
    void set_name(std::string name);
    Zombie(std::string name);
    ~Zombie();
};

Zombie *newZombie(std::string name);
void randomChump(std::string name);
#endif

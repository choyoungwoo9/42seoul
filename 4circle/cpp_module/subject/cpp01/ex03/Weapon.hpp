#ifndef WEAPON_HPP
#define WEAPON_HPP

#include "string"

class Weapon
{
	private:
		std::string type;
	public:
		Weapon(const std::string &param);
		const std::string &getType()const;
		void setType(std::string const &param);
};

#endif

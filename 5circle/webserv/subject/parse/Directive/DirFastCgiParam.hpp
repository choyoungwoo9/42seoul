#ifndef DIRFASTCGIPARAM_HPP
#define DIRFASTCGIPARAM_HPP

#include "../Util/MyUtil.hpp"
#include "../Util/CustomException.hpp"
#include <string>
#include <map>
#include <vector>

using namespace std;

class DirFastCgiParam{
	public:
		DirFastCgiParam &operator =(DirFastCgiParam &param)
		{
			return *this;
		}
		//need implement
		void set_value(string &value)
		{

		}
};

#endif
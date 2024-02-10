#ifndef DIRFASTCGIPASS_HPP
#define DIRFASTCGIPASS_HPP

#include "../Util/MyUtil.hpp"
#include "../Util/CustomException.hpp"
#include <string>
#include <map>
#include <vector>

using namespace std;

class DirFastCgiPass{
	public:
		DirFastCgiPass &operator =(DirFastCgiPass &param)
		{
			return *this;
		}
		//need implement
		void set_value(string &value)
		{

		}
};

#endif
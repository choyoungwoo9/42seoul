#ifndef DIRAUTOINDEX_HPP
#define DIRAUTOINDEX_HPP

#include "../Util/MyUtil.hpp"
#include "../Util/CustomException.hpp"
#include <string>
#include <map>
#include <vector>

using namespace std;

class DirAutoIndex{
	public:
		DirAutoIndex()
		{
			state = "off";
		}

		DirAutoIndex &operator =(DirAutoIndex &param)
		{
			state = param.state;
			return *this;
		}

		void set_value(string &value)
		{
			string str = string_end_trim(value);
			if(str != "on" && str != "off")
			{
				cout << "autoindex must be on or off\n";
				throw DirectiveException();
			}
			state = str;
		}
		string state;
};

#endif
#ifndef DIRSERVERNAME_HPP
#define DIRSERVERNAME_HPP

#include "../Util/MyUtil.hpp"
#include "../Util/CustomException.hpp"
#include <string>
#include <map>
#include <vector>

using namespace std;

//need duplicate check
//need default check

class DirServerName{
	public:
		DirServerName()
		{
		}

		DirServerName &operator =(DirServerName &param)
		{
			for(int i = 0; i < param.name_vector.size(); i++)
				name_vector.push_back(param.name_vector[i]);
			return *this;
		}

		void set_value(string &value)
		{
			string str = string_end_trim(value);
			if(str.empty())
			{
				cout << "server_name empty\n";
				throw DirectiveException();
			}
			name_vector = white_space_split(str);
		}
		vector<string> name_vector;
};

#endif
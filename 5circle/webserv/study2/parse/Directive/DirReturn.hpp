#ifndef DIRRETURN_HPP
#define DIRRETURN_HPP

#include "../Util/MyUtil.hpp"
#include "../Util/CustomException.hpp"
#include <string>
#include <map>
#include <vector>

using namespace std;

class DirReturn{
	public:
		DirReturn()
		{
			is_set = false;
		}

		DirReturn &operator =(DirReturn &param)
		{
			(void) param;
			return *this;
		}

		void set_value(string &value)
		{
			string str = string_end_trim(value);
			vector<string> vt = white_space_split(str);
			if(vt.size() != 2 || vt[0].size() > 3)
			{
				cout << "return error\n";
				throw DirectiveException();
			}
			for(int i = 0; i < vt[0].size(); i ++)
			{
				if(!isdigit(vt[0][i]))
				{
					cout << "return invalid num error\n";
					throw DirectiveException();
				}
			}
			if(is_set)
				return ;
			is_set = true;
			code = atoi(vt[0].c_str());
			URI = vt[1];
		}
		bool is_set;
		int code;
		string URI;
};

#endif
#ifndef DIRCLIENTMAXBODYSIZE_HPP
#define DIRCLIENTMAXBODYSIZE_HPP

#include "../Util/MyUtil.hpp"
#include "../Util/CustomException.hpp"
#include <string>
#include <map>
#include <vector>

using namespace std;

//size 숫자로했는데 이거 맞아 ?
class DirClientMaxBodySize{
	public:
		DirClientMaxBodySize()
		{
			size = 1024;
		}

		DirClientMaxBodySize &operator =(DirClientMaxBodySize &param)
		{
			size = param.size;
			return *this;
		}

		void set_value(string &value)
		{
			string str = string_end_trim(value);
			if(!is_one_word(str))
			{
				cout << "client_max_body_size empty\n";
				throw DirectiveException();
			}

			for(int i = 0; i < str.size()-1; i++)
			{
				if(str[i] < '0' || str[i] > '9')
				{
					cout << "client_max_body_size\n";
					throw DirectiveException();
				}
			}
			string tmp = "0123456789MKGmkg";
			for(int i = 0; i < tmp.size(); i ++)
			{
				if(str[str.size()-1] == tmp[i])
				{
					if(str[str.size()-1] == 'M' || str[str.size()-1] == 'm')
						size = 1024 * atoi(str.c_str());
					else if(str[str.size()-1] == 'K' || str[str.size()-1] == 'k')
						size = 1024 * 1024 * atoi(str.c_str());
					else if(str[str.size()-1] == 'G' || str[str.size()-1] == 'g')
						size = 1024 * 1024 * 1024 * atoi(str.c_str());
					else
						size = atoi(str.c_str());
					return ;
				}
			}
			cout << "client_max_body_size\n";
			throw DirectiveException();
		}
		int size;
};

#endif
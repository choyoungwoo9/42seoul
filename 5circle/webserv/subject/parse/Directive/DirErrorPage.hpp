#ifndef DIRERRORPAGE_HPP
#define DIRERRORPAGE_HPP

#include "../Util/MyUtil.hpp"
#include "../Util/CustomException.hpp"
#include <string>
#include <map>
#include <vector>

using namespace std;

//a ; -> empty가 들어갈 가능성
class DirErrorPage{
	public:
		DirErrorPage(){
			error_num[404] = "HTML/404.html";
			// error_num[404] = "HTML/404.html";
		}
		DirErrorPage &operator =(DirErrorPage &param)
		{
			map<int, string>::iterator it = param.error_num.begin();
			for(;it != param.error_num.end(); it++)
				error_num[it->first] = it->second;
			return *this;
		}
		void set_value(string &value)
		{
			vector<string> vt = white_space_split(value);
			if(vt.size() < 2)
			{
				cout << "error_page need more value\n";
				throw DirectiveException();
			}
			for(int i = 0; i < vt.size()-1; i ++)
			{
				for(int j = 0; j < vt[i].size(); j++)
				{
					if(vt[i][j] < '0' || vt[i][j] > '9')
					{
						cout << "error_page error code need numeric arg\n";
						throw DirectiveException();
					}
					if(atoi(vt[i].c_str()) < 300 || atoi(vt[i].c_str()) > 599)
					{
						cout << "error_page error code need between 300 and 599 value\n";
						throw DirectiveException();
					}
				}
			}
			for(int i = 0; i < vt.size()-1; i ++)
				error_num[atoi(vt[i].c_str())] = vt[vt.size()-1];
		}
		map<int, string> error_num;
};

#endif
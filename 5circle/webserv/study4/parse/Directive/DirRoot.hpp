#ifndef DIRROOT_HPP
#define DIRROOT_HPP

#include "../Util/MyUtil.hpp"
#include "../Util/CustomException.hpp"
#include <string>
#include <map>
#include <vector>

using namespace std;

class DirRoot{
	public:
		DirRoot()
		{
			//기본으로 사용할 페이지 경로작성
			path = "/Users/youngwch/42/5circle/webserv/subject/parse";
		}

		DirRoot &operator =(DirRoot &param)
		{
			path = param.path;
			return *this;
		}
		void set_value(string &value)
		{
			string str = string_end_trim(value);
			if(!is_one_word(str))
			{
				cout << "root\n";
				throw DirectiveException();
			}
			path = str;
		}
		string path;
};

#endif
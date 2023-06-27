#ifndef DIRINDEX_HPP
#define DIRINDEX_HPP

#include "../Util/MyUtil.hpp"
#include "../Util/CustomException.hpp"
#include <string>
#include <map>
#include <vector>

using namespace std;

class DirIndex{
	public:
		DirIndex()
		{
			
		}

		DirIndex &operator =(DirIndex &param)
		{
			for(int i = 0; i < param.index_vector.size(); i++)
				index_vector.push_back(param.index_vector[i]);
			return *this;
		}
		void set_value(string &value)
		{
			string str = string_end_trim(value);
			if(str.empty())
			{
				cout << "index empty\n";
				throw DirectiveException();
			}
			index_vector = white_space_split(str);
		}
		vector<string> index_vector;
};

#endif
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
			index_vector.push_back("index.html");
			index_vector.push_back("index.htm");
		}

		DirIndex &operator =(DirIndex &param)
		{
			index_vector.clear();
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
			for(int i = 0; i < index_vector.size()-1; i ++)
			{
				if(index_vector[i][0] == '/')
				{
					cout << "only the last index directive should be absolute \n";
					throw DirectiveException();
				}
			}
		}
		vector<string> index_vector;
};

#endif
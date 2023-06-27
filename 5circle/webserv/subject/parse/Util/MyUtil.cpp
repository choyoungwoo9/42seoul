#include "MyUtil.hpp"

int is_one_word(string &str)
{
	if(str.empty())
	{
		return 0;
	}
	for(int i = 0; i < str.size(); i ++)
	{
		if(str[i] == ' ' || str[i] == '\t')
		{
			return 0;
		}
	}
	return 1;
}

vector<string> split(string str, string del)
{
	vector<string> ret;
	
	for(int i = str.find(del); i != string::npos; i=str.find(del))
	{
		ret.push_back(str.substr(0, i));
		str.erase(0, i+del.size());
	}
	ret.push_back(str);
	return ret;
}

vector<string> white_space_split(string str) 
{
	vector<string> ret;
	int start = 0;
	int state = 0;
	for(int i = 0; i < str.size(); i ++)
	{
		if(str[i] == ' ' || str[i] == '\t')
		{
			if(state == 0)
				continue;
			if(state == 1)
			{
				ret.push_back(str.substr(start, i-start));
				state = 0;
			}
		}
		else
		{
			if(state == 0)
				start = i;
			state = 1;
		}
	}
	if(state == 1)
		ret.push_back(str.substr(start));
	return ret;
}

string string_end_trim(string str)
{
	int i;
	for(i = str.size()-1; i >= 0; i --)
	{
		if(str[i] == ' ' || str[i] == '\t')
			continue;
		else
			break;
	}
	str = str.substr(0, i+1);
	return str;
}

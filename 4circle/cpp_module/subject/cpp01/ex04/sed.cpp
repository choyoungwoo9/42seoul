#include "sed.hpp"

int get_input(char *arg, std::string &str)
{
	std::ifstream ifs;
	ifs.open(arg);
	if(!ifs.is_open())
	{
		std::cout << "not open !" << std::endl;
		return 0;
	}
	while(1)
	{
		char ch;
		ch = ifs.get();
		if(ch == EOF)
			break ;
		str += ch;
	}
	ifs.close();
	return 1;
}

void change_str(std::string &str, const char *arg, const std::string &s1, const std::string &s2)
{
	std::ofstream ofs;
	ofs.open(arg, std::ofstream::out | std::ofstream::trunc);
	if(s1.empty())
	{
		ofs.close();
		return ;
	}
	for(int i = 0; i < (int)str.size();)
	{
		if(str.compare(i, s1.size(), s1) == 0)
		{
			str.erase(i, s1.size());
			str.insert(i, s2);
			i += s2.size();
		}
		else
			i ++;
	}
	ofs << str;
	ofs.close();
}
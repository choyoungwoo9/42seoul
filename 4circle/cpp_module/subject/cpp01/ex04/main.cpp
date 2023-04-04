#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char **argv)
{
	if(argc != 4)
	{
		std::cout << "invalid argv" << std::endl;
		return 0;
	}
	std::ifstream ifs;
	ifs.open(argv[1]);
	if(ifs.fail())
	{
		std::cout << "error" << std::endl;
		return 0;
	}
	while(!ifs.eof())
	{
		std::string a;
		ifs >> a;
		std::cout << a << std::endl;
	}
	ifs.close();
}

#include "sed.hpp"

int main(int argc, char **argv)
{
	if(argc != 4)
	{
		std::cout << "invalid argv" << std::endl;
		return 1;
	}
	std::string str;
	if(!get_input(argv[1], str))
		return 1;
	change_str(str, argv[1], argv[2], argv[3]);
}

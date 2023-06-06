#include "RPN.hpp"

int main(int argc, char **argv)
{
	try
	{
		if(argc != 2)
			throw std::exception();
		RPN(argv[1]);
	}
	catch(std::exception &e)
	{
		std::cout << "Error" << std::endl;
		return 1;
	}
	return 0;
}
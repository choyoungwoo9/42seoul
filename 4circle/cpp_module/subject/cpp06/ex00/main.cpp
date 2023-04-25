#include "FtConvert.hpp"

int main(int argc, char **argv)
{
	if(argc != 2)
		return 1;
	try
	{
		if(FtConvert::is_integer(argv[1]))
		{
			FtConvert::print_integer(argv[1]);
		}
		else if(FtConvert::is_double(argv[1]))
		{
			FtConvert::print_double(argv[1]);
		}
		else if(FtConvert::is_float(argv[1]))
		{
			FtConvert::print_float(argv[1]);
		}
		else
		{
			FtConvert::print_char(argv[1]);
		}	
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}
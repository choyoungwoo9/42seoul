#include "ScalarConverter.hpp"

int main(int argc, char **argv)
{
	std::cout << std::numeric_limits<double>::max() << std::endl;
	std::cout << std::numeric_limits<float>::max() << std::endl;
	if(argc != 2)
		return 1;
	ScalarConverter::Convert(argv[1]);
}

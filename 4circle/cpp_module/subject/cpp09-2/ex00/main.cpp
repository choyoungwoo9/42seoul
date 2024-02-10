#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "MUST NEED ONE ARG\n";
		return 1;
	}
	try
	{
		BitcoinExchange bt(argv[1]);
		bt.memorizeData();
		bt.processInput();
	}
	catch (const std::runtime_error &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
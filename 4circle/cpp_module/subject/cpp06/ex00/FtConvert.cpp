#include "FtConvert.hpp"

FtConvert::FtConvert()
{

}
FtConvert::~FtConvert()
{

}
FtConvert::FtConvert(FtConvert &param)
{
	(void)param;
}
FtConvert &FtConvert::operator =(FtConvert &param)
{
	(void)param;
	return *this;
}
void FtConvert::int_to_char_print(int num)

{
	if(num >= 32 && num <= 126)
		std::cout << "char: '" << static_cast<char>(num) << "'" << std::endl;
	else if((num >= 0 && num <= 31) || num == 127)
		std::cout << "char: " << "Non displayable" << std::endl;
	else
		std::cout << "char: " << "impossible" << std::endl;
}

void FtConvert::check_null(char *str)
{
	if(!str)
		throw(std::exception());
}

int FtConvert::is_integer(char *str)
{
	check_null(str);
	if(!*str)
		return 0;
	char *ptr;
	long num = std::strtol(str, &ptr, 10);
	if(*ptr)
		return 0;
	else
	{
		if(num > INT32_MAX || num < INT32_MIN)
			return 0;
		return 1;
	}
}
int FtConvert::is_double(char *str)
{
	check_null(str);
	if(!*str)
		return 0;
	char *ptr;
	double num = std::strtod(str, &ptr);
	(void)num;
	if(*ptr)
		return 0;
	else
		return 1;
}
int FtConvert::is_float(char *str)
{
	check_null(str);
	if(!*str)
		return 0;
	char *ptr;
	float num = std::strtod(str, &ptr);
	(void)num;
	std::string f = "f";
	if(!*ptr || f == ptr)
		return 1;
	else
		return 0;
}

void FtConvert::print_integer(char *str)
{
	check_null(str);
	char *ptr;
	int num = static_cast<int>(std::strtol(str, &ptr, 10));
	int_to_char_print(num);
	std::cout << "int: " << num << std::endl;
	std::cout << "float: " << static_cast<float>(num) << ".0f" << std::endl;
	std::cout << "double: " << static_cast<double>(num) << ".0" << std::endl;
}
void FtConvert::print_double(char *str)
{
	check_null(str);
	char *ptr;
	double num = std::strtod(str, &ptr);
	if(!(num - static_cast<int>(num)))
	{
		int_to_char_print(num);
		std::cout << "int: " << static_cast<int>(num) << std::endl;
		std::cout << "float: " << static_cast<float>(num) << ".0f" << std::endl;
		std::cout << "double: " << static_cast<double>(num) << ".0" << std::endl;
	}
	else
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		if(num == INFINITY)
		{
			std::cout << "float: +inf" << std::endl;
			std::cout << "double: +inf" << std::endl;
		}
		else
		{
			std::cout << "float: " << static_cast<float>(num) << "f" << std::endl;
			std::cout << "double: " << num << std::endl;
		}
	}
}
void FtConvert::print_float(char *str)
{
	check_null(str);
	char *ptr;
	float num = static_cast<float>(std::strtod(str, &ptr));
	if(!(num - static_cast<int>(num)))
	{
		int_to_char_print(static_cast<int>(num));
		std::cout << "int: " << static_cast<int>(num) << std::endl;
		std::cout << "float: " << num << ".0f" << std::endl;
		std::cout << "double: " << static_cast<double>(num) << ".0" << std::endl;
	}
	else
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: " << "impossible" << std::endl;
		if(num == INFINITY)
		{
			std::cout << "float: +inf" << std::endl;
			std::cout << "double: +inf" << std::endl;
		}
		else
		{
			std::cout << "float: " << num << "f" << std::endl;
			std::cout << "double: " << static_cast<double>(num) << std::endl;
		}
	}
}
void FtConvert::print_char(char *str)
{
	check_null(str);
	if(str[1] == '\0')
		int_to_char_print(static_cast<int>(str[0]));
	else
		std::cout << "char: impossible" << std::endl;
	std::cout << "int: " << "impossible" << std::endl;
	std::cout << "float: " << "impossible" << std::endl;
	std::cout << "double: " << "impossible" << std::endl;
}


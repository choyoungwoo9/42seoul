#include "ScalarConverter.hpp"

void ScalarConverter::int_to_char_print(int num)
{
	if(num >= 32 && num <= 126)
		std::cout << "char: '" << static_cast<char>(num) << "'" << std::endl;
	else if((num >= 0 && num <= 31) || num == 127)
		std::cout << "char: " << "Non displayable" << std::endl;
	else if(num < 0 || num > CHAR_MAX)
		std::cout << "char: " << "impossible" << std::endl;
}

void ScalarConverter::check_null(char *str)
{
	if(!str)
		throw(std::exception());
}

int ScalarConverter::is_integer(char *str)
{
	if(!*str)
		return 0;
	char *ptr;
	long num = std::strtol(str, &ptr, 10);
	if(*ptr)
		return 0;
	else
	{
		if(num > INT_MAX || num < INT_MIN)
			return 0;
		return 1;
	}
}
int ScalarConverter::is_double(char *str)
{
	if(!*str)
		return 0;
	char *ptr;
	double num = std::strtod(str, &ptr);
	static_cast<void>(num);
	if(*ptr)
		return 0;
	else
		return 1;
}
int ScalarConverter::is_float(char *str)
{
	if(!*str)
		return 0;
	char *ptr;
	float num = std::strtod(str, &ptr);
	static_cast<void>(num);
	std::string f = "f";
	if(f == ptr)
		return 1;
	else
		return 0;
}

void ScalarConverter::print_integer(char *str)
{
	char *ptr;
	int num = static_cast<int>(std::strtol(str, &ptr, 10));
	int_to_char_print(num);
	std::cout << "int: " << num << std::endl;
	std::cout << "float: " << static_cast<float>(num) << ".0f" << std::endl;
	std::cout << "double: " << static_cast<double>(num) << ".0" << std::endl;
}

void ScalarConverter::print_double(char *str)
{
	char *ptr;
	double num = std::strtod(str, &ptr);
	if(static_cast<double>(static_cast<int>(num)) == num)
	{
		int_to_char_print(static_cast<int>(num));
		std::cout << "int: " << static_cast<int>(num) << std::endl;
		std::cout << "float: " << static_cast<float>(num) << ".0f" << std::endl;
		std::cout << "double: " << static_cast<double>(num) << ".0" << std::endl;
	}
	else
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		if(std::isinf(num))
		{
			if(num > 0.0f)
			{
				std::cout << "float: +inff" << std::endl;
				std::cout << "double: +inf" << std::endl;
			}
			else
			{
				std::cout << "float: -inff" << std::endl;
				std::cout << "double: -inf" << std::endl;
			}
		}
		else
		{
			std::cout << "float: " << static_cast<float>(num) << "f" << std::endl;
			std::cout << "double: " << num << std::endl;
		}
	}
}
void ScalarConverter::print_float(char *str)
{
	char *ptr;
	float num = static_cast<float>(std::strtod(str, &ptr));
	if(static_cast<float>(static_cast<int>(num)) == num)
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
		if(std::isinf(num))
		{
			if(num > 0.0)
			{
				std::cout << "float: +inff" << std::endl;
				std::cout << "double: +inf" << std::endl;
			}
			else
			{
				std::cout << "float: -inff" << std::endl;
				std::cout << "double: -inf" << std::endl;
			}
		}
		else
		{
			std::cout << "float: " << num << "f" << std::endl;
			std::cout << "double: " << static_cast<double>(num) << std::endl;
		}
	}
}
void ScalarConverter::print_char(char *str)
{
	if(str[0] && str[1] == '\0')
		int_to_char_print(static_cast<int>(str[0]));
	else
		std::cout << "char: impossible" << std::endl;
	std::cout << "int: " << "impossible" << std::endl;
	std::cout << "float: " << "impossible" << std::endl;
	std::cout << "double: " << "impossible" << std::endl;
}

void ScalarConverter::Convert(char *str)
{
	try
	{
		check_null(str);
		if(ScalarConverter::is_integer(str))
		{
			ScalarConverter::print_integer(str);
		}
		else if(ScalarConverter::is_double(str))
		{
			ScalarConverter::print_double(str);
		}
		else if(ScalarConverter::is_float(str))
		{
			ScalarConverter::print_float(str);
		}
		else
		{
			ScalarConverter::print_char(str);
		}
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
}
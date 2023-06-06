#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <exception>
#include <iostream>
#include <string>
#include <cmath>

class ScalarConverter
{
	public:
		static void Convert(char *str);
	private:
		ScalarConverter();
		~ScalarConverter();
		ScalarConverter(ScalarConverter &param);
		ScalarConverter &operator =(ScalarConverter &param);
		static void check_null(char *str);
		static void int_to_char_print(int num);
		static int is_integer(char *str);
		static int is_double(char *str);
		static int is_float(char *str);
		static void print_integer(char *str);
		static void print_double(char *str);
		static void print_float(char *str);
		static void print_char(char *str);
};

#endif
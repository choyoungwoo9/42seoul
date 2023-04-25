#ifndef FTCONVERT_HPP
#define FTCONVERT_HPP

#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>

class FtConvert
{
	public:
		static int is_integer(char *str);
		static int is_double(char *str);
		static int is_float(char *str);

		static void print_integer(char *str);
		static void print_double(char *str);
		static void print_float(char *str);
		static void print_char(char *str);
	private:
		FtConvert();
		~FtConvert();
		FtConvert(FtConvert &param);
		FtConvert &operator =(FtConvert &param);
		static void check_null(char *str);
		static void int_to_char_print(int num);
};

#endif
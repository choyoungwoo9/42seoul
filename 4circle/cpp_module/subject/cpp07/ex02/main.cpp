#include "Array.hpp"
#include <iostream>
#include <exception>

int main()
{
	//parameter constructor test
	try
	{
		Array<int> int_ar(5);
		for(unsigned int i = 0; i < int_ar.size(); i ++)
			std::cout << int_ar[i] << std::endl;
		std::cout << "size : " << int_ar.size() << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	
	//default constructor test
	try
	{
		Array<int> int_ar;
		std::cout << int_ar[0];
	}
	catch(std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	//copy constructor test
	try
	{
		Array<float> float_ar1(5);
		for(int i = 0; i < 5; i ++)
			float_ar1[i] = i + 0.1;
		Array<float> float_ar2(float_ar1);
		for(int i = 0; i < 5; i ++)
		{
			std::cout << "float origin : " << float_ar1[i] << std::endl;
			std::cout << "float copy : " << float_ar2[i] << std::endl;
		}
		std::cout << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	//assign test
	try
	{
		Array<float> float_ar1(5);
		for(int i = 0; i < 5; i ++)
			float_ar1[i] = i + 0.1;

		Array<float> float_ar2(3);
		float_ar2 = float_ar1;
		for(int i = 0; i < 5; i ++)
		{
			std::cout << "float origin : " << float_ar1[i] << std::endl;
			std::cout << "float copy : " << float_ar2[i] << std::endl;
		}
		std::cout << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	//check leak
	//system("leaks Array");
}
#include <string>
#include <iostream>

int main(int argc, char **argv)
{
	if(argc != 2)
		return 1;
	char *ptr;
	
	printf("\n\nlong start\n\n");
	int num3 = std::atoi(argv[1]);
	printf("||%s||\n", ptr);
	std::cout << "int : " << num3 << std::endl;
	std::cout << "float : " << static_cast<float>(num3) << "f" << std::endl;
	std::cout << "double : " << static_cast<double>(num3) << std::endl;
	
	printf("\n\nfloat start\n\n");
	float num = std::atof(argv[1]);
	printf("||%s||\n", ptr);
	std::cout << "int : " << "imposiible" << std::endl;
	std::cout << "float : " << num << "f" << std::endl;
	std::cout << "double : " << static_cast<double>(num) << std::endl;


    const char* str1 = "3.";
    const char* str2 = "3.0";

    char* endptr;
    float num5 = strtof(str1, &endptr);
    if (*endptr == '.') {
        std::cout << "Input string " << str1 << " is a floating point value without a fractional part\n";
    }

    float num6 = strtof(str2, &endptr);
    if (*endptr == '0') {
        std::cout << "Input string " << str2 << " is a floating point value with a fractional part of zero\n";
    }
}

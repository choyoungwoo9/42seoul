#include <iostream>

int main()
{
    std::string str = "HI THIS IS BRAIN";
    std::string *stringPTR = &str;
    std::string &stringREF = str;
    std::cout << "variable address by var: " << &str << std::endl;
    std::cout << "variable address by ptr: " << stringPTR << std::endl;
    std::cout << "variable address by ref: " << &stringREF << std::endl;

    std::cout << "value by var: " << str << std::endl;
    std::cout << "value by ptr: " << *stringPTR << std::endl;
    std::cout << "value by ref: " << stringREF << std::endl;
}

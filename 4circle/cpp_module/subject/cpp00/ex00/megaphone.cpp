#include <iostream>

int main(int argc, char **argv)
{
    std::string str;
    if(argc == 1)
        str = "loud and unbearable feedback noise *";
    for(int i = 1; i < argc; i ++)
    {
        str.append(argv[i]);
    }
    for(int i = 0; i < (int)str.size(); i++)
        str[i] = std::toupper(str[i]);
}
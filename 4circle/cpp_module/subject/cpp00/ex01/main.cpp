#include "main.h"

int main()
{
    std::string input;
    PhoneBook book;
    while(1)
    {
        std::cout << "WRITE ADD || SEARCH || EXIT?" << std::endl;
        std::cin >> input;
        if(input == "EXIT")
        {
            break;
        }
        else if(input == "ADD")
        {
            book.add_phone_book();
        }
        else if(input == "SEARCH")
        {
            book.search_phone_book();
        }
        else
        {
            std::cout << input << " IS WRONG ORDER" << std::endl;
        }
    }
}
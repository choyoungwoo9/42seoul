#ifndef PARSED_DIRECTIVE_HPP
#define PARSED_DIRECTIVE_HPP

#include <string>

using namespace std;

class ParsedDirective {
private:
public:
	ParsedDirective(string name, string value)
	{
		this->name = name;
		this->value = value;
	}
    string name;
    string value;
};

#endif
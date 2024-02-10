#ifndef CUSTOMEXCEPTION_HPP
#define CUSTOMEXCEPTION_HPP

#include <exception>

using namespace std;

class ParseException : exception
{
public:
	const char *what() const throw()
	{
		return "Parse Error";
	}
};

class ContextException : exception
{
public:
	const char *what() const throw()
	{
		return "Context Error";
	}
};

class DirectiveException : exception
{
public:
	const char *what() const throw()
	{
		return "Directive Error";
	}
};

#endif
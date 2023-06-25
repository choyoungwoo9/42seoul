#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <cctype>

#include "CustomException.hpp"
#include "Directive.hpp"

using namespace std;

class Context {
private:
public:
	Context(string name, string str)
	{
		this->name = name;
		parse_conf(str);
	}
	Context(string name, string str, string uri)
	{
		this->name = name;
		this->uri = uri;
		parse_conf(str);
	}
    string name;
	string uri;
    vector<Directive> directives;
    vector<Context> subContexts;
	void parse_conf(string &str);
	void print_conf();
private:
	string get_key(int &i, string &str);
	int is_context(string &str);
	string get_bracket(int &i, string &str);
	string get_uri(int &i, string &str);
	string get_value(int &i, string &str);
};

#endif
#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <cctype>

#include "../Directive/AllDirective.hpp"
#include "../Util/CustomException.hpp"
#include "../Util/MyUtil.hpp"
#include "../Util/ParsedDirective.hpp"


using namespace std;


class Context {
public:
	//가장처음 nginx.conf 파싱할때 호출
	Context(string name, string str, int main_flag);
	//파싱하다가 도중에 context 발견될때 호출
	Context(string name, string str);
	//파싱하다가 context중 location 발견될때 호출
	Context(string name, string str, string uri);

	Context(Context &param)
	{
		
	}
	Context &operator =(Context &param)
	{
		return *this;
	}

	int main_flag;
	AllDirective directives;
    string name;
	string uri;
    vector<ParsedDirective> parsed_directives;
    vector<Context> subContexts;
	void print_raw_conf();

	void print_conf();

private:
	void parse_conf(string &str);
	void context_validate();
	void set_directive();

	string get_key(int &i, string &str);
	int is_context(string &str);
	string get_bracket(int &i, string &str);
	string get_uri(int &i, string &str);
	string get_value(int &i, string &str);

	void sub_context_check(vector<string> &unique, vector<string> &can, map<string, int> &cnt);
	void directive_check(vector<string> &unique, vector<string> &can, map<string, int> &cnt);
	void check_unique_and_valid_directive(vector<string> &unique, vector<string> &can, map<string, int> &cnt);

	void main_context_validate();
	void events_context_validate();
	void http_context_validate();
	void server_context_validate();
	void location_context_validate();

	void categorize_directive(ParsedDirective &parsed_directives);
};

#endif
#ifndef MYUTIL_HPP
#define MYUTIL_HPP

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int is_one_word(string &str);
vector<string> split(string str, string del);
vector<string> white_space_split(string str);
string string_end_trim(string str);

#endif
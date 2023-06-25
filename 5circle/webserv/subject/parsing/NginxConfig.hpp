#ifndef NGINXCONFIG_HPP
#define NGINXCONFIG_HPP
#include "Context.hpp"

using namespace std;

class NginxConfig{
private:
public:
	NginxConfig(string &str)
	:mainContext("main", str)
	{};
	Context mainContext;
};

#endif
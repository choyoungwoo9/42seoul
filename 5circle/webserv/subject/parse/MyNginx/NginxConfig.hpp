#ifndef NGINXCONFIG_HPP
#define NGINXCONFIG_HPP
#include "../Context/Context.hpp"

using namespace std;

#include <vector>
#include <set>
#include <string>
#include "../Util/MyUtil.hpp"
#include "../Structrue.hpp"

class NginxConfig{
private:
public:
	NginxConfig(string &str);
	Context mainContext;
	void check_duplicate_server_name();
	void check_duplicate_location();
	vector<pair<string, int> > find_all_port();
	void set_default_server();

	sResponseMsg make_response(sReqMsg &req, string &address, string &port);
	
	
	Context &find_server_by_full_address(string &host, string &full_address);
	Context &find_http_context();
	Context &find_virtual_server(string &host, string &address, string &port);
};


#endif
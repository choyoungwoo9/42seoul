#ifndef NGINXCONFIG_HPP
#define NGINXCONFIG_HPP
#include "../Context/Context.hpp"

using namespace std;

#include <vector>
#include <set>
#include <string>
#include <dirent.h>
#include "../Util/MyUtil.hpp"
#include "../Structrue.hpp"
#include "../IO/IoUtil.hpp"

const string default_500_path = "/Users/youngwch/42/5circle/webserv/subject/parse/HTML/500.html";
const string default_404_path = "/Users/youngwch/42/5circle/webserv/subject/parse/HTML/404.html";
const string default_413_path = "/Users/youngwch/42/5circle/webserv/subject/parse/HTML/413.html";

void error_page_process(sResponseMsg &res, sReqMsg &req, Context &selected_context, Context &origin_server, int redirect_count);
bool max_body_check(sReqMsg &req, Context &server);
void find_file_process(sResponseMsg &res, sReqMsg &req, Context &selected_context, Context &origin_server, int redirect_count);
void index_process(sResponseMsg &res, sReqMsg &req, Context &selected_context, Context &origin_server, int redirect_count);
void return_process(sResponseMsg &res, sReqMsg &req, Context &selected_context, Context &origin_server, int redirect_count);
void autoindex_process(sResponseMsg &res, sReqMsg &req, Context &selected_context, Context &origin_server, int redirect_count);

void make_response_by_server(sResponseMsg &res, sReqMsg &req, Context &server, int redirect_count);


class NginxConfig{
private:
public:

	NginxConfig(string &str);
	void config_server();
	vector<pair<string, int> > find_all_port();
	sResponseMsg make_response(sReqMsg &req, string &address, string &port);
	Context mainContext;
private:

	string raw_config;

	void check_duplicate_server_name();
	void check_duplicate_location();
	void set_default_server();

	Context &find_server_by_full_address(string &host, string &full_address);
	Context &find_http_context();
	Context &find_virtual_server(string &host, string &address, string &port);
};


#endif
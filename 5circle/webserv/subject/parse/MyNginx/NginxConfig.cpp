#include "NginxConfig.hpp"

NginxConfig::NginxConfig(string &str)
:mainContext("main", str, 1)
{}

void NginxConfig::check_duplicate_server_name()
{
	map<string, set<string> >mp;
	mainContext.get_all_server(mp);
}

vector<pair<string, int> > NginxConfig::find_all_port()
{
	vector<pair<string, int> > ret;
	map<string, set<string> >mp;
	mainContext.get_all_server(mp);
	for(map<string, set<string> >::iterator it = mp.begin(); it != mp.end(); it ++)
	{
		ret.push_back(pair<string, int>(split(it->first, ":")[0], atoi(split(it->first, ":")[1].c_str())));
	}
	return ret;
}


void NginxConfig::set_default_server()
{
	Context &http = find_http_context();
	if(http.name == "main")
		return ;
	set<string> default_server_set = http.get_default_server();
	for(int j = 0; j < http.subContexts.size(); j++)
	{
		if(http.subContexts[j].name != "server")
			continue;
		string &cur_addr = http.subContexts[j].directives.listen.address;
		if(default_server_set.find(cur_addr) == default_server_set.end())
		{
			http.subContexts[j].directives.listen.is_default_server = true;
			default_server_set.insert(cur_addr);
		}
	}
}

Context &NginxConfig::find_http_context()
{
	for(int i = 0; i < mainContext.subContexts.size(); i ++)
	{
		if(mainContext.subContexts[i].name == "http")
		{
			return mainContext.subContexts[i];
		}
	}
	return mainContext;
}

Context &NginxConfig::find_virtual_server(string &host, string &address, string &port)
{
	Context &http = find_http_context();
	if(http.name == "main")
		return mainContext;
	string full_address = (address + ':') + port;
	for(int i = 0; i < http.subContexts.size(); i++)
	{
	
		if(http.subContexts[i].directives.listen.address != full_address)
			continue;
		vector<string> server_names = http.subContexts[i].directives.server_name.name_vector;
		for(int j = 0; j < server_names.size(); j++)
		{
			if(host == server_names[j])
				return subContext
		}
	}
}

//추후 cgi처리 필요함 지금코드는 cgi 고려없음
sResponseMsg NginxConfig::make_response(sReqMsg &req, string &address, string &port)
{
	Context &server = find_virtual_server(req.host, req.requestTarget);
	//구성된 서버를 못찾은 상황인데 이런상황이 있을까 ?
	// if(server.name == "main")
	// {
	// 	return ~~;
	// }
	// server.directives
}
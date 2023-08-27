#include "NginxConfig.hpp"

NginxConfig::NginxConfig(string &str)
:mainContext()
{
	raw_config = str;
}

void NginxConfig::config_server()
{
	mainContext.config_main(raw_config);
	check_duplicate_server_name();
	check_duplicate_location();
	set_default_server();
}

void NginxConfig::check_duplicate_server_name()
{
	map<string, set<string> >mp;
	mainContext.get_all_server(mp);
}

void NginxConfig::check_duplicate_location()
{
	Context &http = find_http_context();
	if(http.name == "main")
		return ;
	for(int i = 0; i < http.subContexts.size(); i++)
	{
		set<string> uri_st;
		for(int j = 0; j < http.subContexts[i].subContexts.size(); j ++)
		{
			string cur_uri = http.subContexts[i].subContexts[j].uri;
			if(uri_st.find(cur_uri) != uri_st.end())
			{
				cout << "duplicate location uri\n";
				throw DirectiveException();
			}
			uri_st.insert(cur_uri);
		}
	}
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

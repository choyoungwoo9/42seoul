#include "Context.hpp"

Context::Context()
{
}

Context::Context(string name, string str)
{
	this->name = name;
	parse_conf(str);
	main_flag = 0;
}

void Context::config_main(string str)
{
	this->name = "main";
	this->main_flag = 1;
	parse_conf(str);
	context_validate();
	AllDirective default_directive;
	set_directive(default_directive);
}


Context::Context(string name, string str, string uri)
{
	this->name = name;
	this->uri = uri;
	parse_conf(str);
}

void Context::print_conf()
{
	cout << "/////////////"<< name << " Context print" <<  "/////////////" << endl;
	cout << "name : " << name << endl;
	cout << "uri : " << uri << endl;
	cout << endl;
	directives.print_all_key_value();
	for(int i = 0; i < subContexts.size(); i ++)
	{
		cout << "/////////////" << name << "\'s " << i+1 << "th subContexts print" <<  "/////////////" << endl;
		subContexts[i].print_conf();
		cout << "/////////////" << i+1 << " subContexts end" <<  "/////////////" << endl;
	}
	cout << "///////////// " << name << "  Context end" <<  "/////////////" << endl;
}

void Context::print_raw_conf()
{
	cout << "name : " << name << endl;
	for(int i = 0; i < parsed_directives.size(); i ++)
		cout << parsed_directives[i].name << " : " << parsed_directives[i].value << endl;
	cout << "uri : " << uri << endl;
	for(int i = 0; i < subContexts.size(); i ++)
	{
		cout << "/////////////" << i+1 << " subContexts print" <<  "/////////////" << endl;
		subContexts[i].print_raw_conf();
	}
}

void Context::get_all_server(map<string, set<string> > &mp)
{
	if(name == "main")
	{
		for(int i = 0; i < subContexts.size(); i ++)
		{
			if(subContexts[i].name == "http")
				subContexts[i].get_all_server(mp);
		}
		return ;
	}
	if(name == "http")
	{
		for(int i = 0; i < subContexts.size(); i ++)
		{
			if(subContexts[i].name == "server")
				subContexts[i].get_all_server(mp);
		}
		return ;
	}
	else if(name == "server")
	{
		for(int i = 0; i < directives.server_name.name_vector.size(); i ++)
		{
			string &cur_server_name = directives.server_name.name_vector[i];
			string &cur_address = directives.listen.address;
			// cout << cur_server_name << "/" << cur_address << endl;
			if(mp[cur_address].find(cur_server_name) != mp[cur_address].end())
			{
				cout << cur_address << " " << cur_server_name << "dulicate server name" << endl;
				throw DirectiveException();
			}
			mp[directives.listen.address].insert(cur_server_name);
		}
		return ;
	}
}


set<string> Context::get_default_server()
{
	set<string> ret;
	if(this->name != "http")
	{
		cout << "only http context do default_server check\n";
		throw DirectiveException();
	}
	for(int i = 0; i < subContexts.size(); i++)
	{
		if(subContexts[i].name != "server")
			continue;
		if(subContexts[i].directives.listen.is_default_server == true)
		{
			if(ret.find(subContexts[i].directives.listen.address) != ret.end())
			{
				cout << "duplicate server_name\n";
				throw DirectiveException();
			}
			ret.insert(subContexts[i].directives.listen.address);
		}
	}
	return ret;
}

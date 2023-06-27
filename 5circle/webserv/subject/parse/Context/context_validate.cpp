#include "Context.hpp"

void Context::sub_context_check(vector<string> &unique, vector<string> &can, map<string, int> &cnt)
{
	for(int i = 0; i < subContexts.size(); i ++)
	{
		int flag = 1;
		for(int j = 0; j < unique.size(); j++)
		{
			if(subContexts[i].name == unique[j])
			{
				flag = 0;
				cnt[unique[j]] ++;
				break;
			}
		}
		for(int j = 0; j < can.size(); j++)
		{
			if(subContexts[i].name == can[j])
			{
				flag = 0;
				break;
			}
		}
		if(flag)
		{
			cout << subContexts[i].name << " invalid subContexts" << endl;
			throw ContextException();
		}
	}
}

void Context::directive_check(vector<string> &unique, vector<string> &can, map<string, int> &cnt)
{
	for(int i = 0; i < parsed_directives.size(); i ++)
	{
		int flag = 1;
		for(int j = 0; j < unique.size(); j++)
		{
			if(parsed_directives[i].name == unique[j])
			{
				flag = 0;
				cnt[unique[j]] ++;
				break;
			}
		}
		for(int j = 0; j < can.size(); j++)
		{
			if(parsed_directives[i].name == can[j])
			{
				flag = 0;
				break;
			}
		}
		if(flag)
		{
			cout << parsed_directives[i].name << " invalid parsed_directives" << endl;
			throw ContextException();
		}
	}
}

void Context::check_unique_and_valid_directive(vector<string> &unique, vector<string> &can, map<string, int> &cnt)
{
	//map에 context와 directive를 담는다.
	//만약 담을 요소가 unique나 can에 없으면 throw
	sub_context_check(unique, can, cnt);
	directive_check(unique, can, cnt);
	for(int i = 0; i < unique.size(); i ++)
	{
		// cout << ct.name << "/////" << it.first << endl;
		//unique한 directive가 2개이상 있으면 throw 
		if(cnt[unique[i]] > 1)
		{
			cout << unique[i] << " Not Duplicated" << endl;
			throw ContextException();
		}
	}
}

void Context::main_context_validate()
{
	vector<string> unique;
	vector<string> can;
	map<string, int> cnt;

	unique.push_back("http");
	unique.push_back("events");

	check_unique_and_valid_directive(unique, can, cnt);
	if(cnt["events"] != 1)
	{
		cout << "We need events Context" << endl;
		throw ContextException();
	}
}

void Context::events_context_validate()
{
	vector<string> unique;
	vector<string> can;
	map<string, int> cnt;

	check_unique_and_valid_directive(unique, can, cnt);
}

void Context::http_context_validate()
{
	vector<string> unique;
	vector<string> can;
	map<string, int> cnt;

	unique.push_back("root");
	unique.push_back("autoindex");
	can.push_back("server");
	can.push_back("client_max_body_size");
	can.push_back("error_page");
	can.push_back("index");
	can.push_back("fastcgi_param");

	check_unique_and_valid_directive(unique, can, cnt);
}

void Context::server_context_validate()
{
	vector<string> unique;
	vector<string> can;
	map<string, int> cnt;

	unique.push_back("root");
	unique.push_back("autoindex");
	can.push_back("location");
	can.push_back("server_name");
	can.push_back("listen");
	can.push_back("client_max_body_size");
	can.push_back("error_page");
	can.push_back("index");
	can.push_back("fastcgi_param");

	check_unique_and_valid_directive(unique, can, cnt);
}

void Context::location_context_validate()
{
	vector<string> unique;
	vector<string> can;
	map<string, int> cnt;

	unique.push_back("root");
	unique.push_back("autoindex");
	can.push_back("location");
	can.push_back("client_max_body_size");
	can.push_back("error_page");
	can.push_back("index");
	can.push_back("fastcgi_param");
	can.push_back("fastcgi_pass");

	check_unique_and_valid_directive(unique, can, cnt);
}

void Context::context_validate()
{
	if(name == "main" && main_flag)
		main_context_validate();
	else if(name == "events")
		events_context_validate();
	else if(name == "http")
		http_context_validate();
	else if(name == "server")
		server_context_validate();
	else if(name == "location")
		location_context_validate();
	else
	{
		cout << "invalid context" << endl;
		throw ContextException();
	}
	for(int i = 0; i < subContexts.size(); i++)
		subContexts[i].context_validate();
}
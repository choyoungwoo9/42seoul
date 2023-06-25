#include "Context.hpp"
#include "CustomException.hpp"

void sub_context_check(Context &ct, vector<string> &unique, vector<string> &can, map<string, int> &cnt)
{
	for(int i = 0; i < ct.subContexts.size(); i ++)
	{
		int flag = 1;
		for(int j = 0; j < unique.size(); j++)
		{
			if(ct.subContexts[i].name == unique[j])
			{
				flag = 0;
				cnt[unique[j]] ++;
				break;
			}
		}
		for(int j = 0; j < can.size(); j++)
		{
			if(ct.subContexts[i].name == can[j])
			{
				flag = 0;
				break;
			}
		}
		if(flag)
		{
			cout << ct.subContexts[i].name << " invalid subContexts" << endl;
			throw ContextException();
		}
	}
}

void directive_check(Context &ct, vector<string> &unique, vector<string> &can, map<string, int> &cnt)
{
	for(int i = 0; i < ct.directives.size(); i ++)
	{
		int flag = 1;
		for(int j = 0; j < unique.size(); j++)
		{
			if(ct.directives[i].name == unique[j])
			{
				flag = 0;
				cnt[unique[j]] ++;
				break;
			}
		}
		for(int j = 0; j < can.size(); j++)
		{
			if(ct.directives[i].name == can[j])
			{
				flag = 0;
				break;
			}
		}
		if(flag)
		{
			cout << ct.directives[i].name << " invalid directives" << endl;
			throw ContextException();
		}
	}
}

void main_context_validate(Context &ct)
{
	vector<string> unique;
	vector<string> can;
	map<string, int> cnt;

	unique.push_back("http");
	unique.push_back("events");
	//map에 context와 directive를 담는다.
	//만약 담을 요소가 unique나 can에 없으면 throw
	sub_context_check(ct, unique, can, cnt);
	directive_check(ct, unique, can, cnt);
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
	if(cnt["events"] != 1)
	{
		cout << "We need events Context" << endl;
		throw ContextException();
	}
}

void events_context_validate(Context &ct)
{
	vector<string> unique;
	vector<string> can;
	map<string, int> cnt;

	sub_context_check(ct, unique, can, cnt);
	directive_check(ct, unique, can, cnt);
	for(int i = 0; i < unique.size(); i ++)
	{
		if(cnt[unique[i]] > 1)
		{
			cout << unique[i] << " Duplicated" << endl;
			throw ContextException();
		}
	}
}

void http_context_validate(Context &ct)
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

	sub_context_check(ct, unique, can, cnt);
	directive_check(ct, unique, can, cnt);
	for(int i = 0; i < unique.size(); i ++)
	{
		if(cnt[unique[i]] > 1)
		{
			cout << unique[i] << " Duplicated" << endl;
			throw ContextException();
		}
	}
}

void server_context_validate(Context &ct)
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

	sub_context_check(ct, unique, can, cnt);
	directive_check(ct, unique, can, cnt);
	for(int i = 0; i < unique.size(); i ++)
	{
		if(cnt[unique[i]] > 1)
		{
			cout << unique[i] << " Duplicated" << endl;
			throw ContextException();
		}
	}
}

void location_context_validate(Context &ct)
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

	sub_context_check(ct, unique, can, cnt);
	directive_check(ct, unique, can, cnt);
	for(int i = 0; i < unique.size(); i ++)
	{
		if(cnt[unique[i]] > 1)
		{
			cout << unique[i] << " Duplicated" << endl;
			throw ContextException();
		}
	}
}

void context_validate(Context &ct)
{
	if(ct.name == "main")
	{
		main_context_validate(ct);
	}
	else if(ct.name == "events")
	{
		events_context_validate(ct);
	}
	else if(ct.name == "http")
	{
		http_context_validate(ct);
	}
	else if(ct.name == "server")
	{
		server_context_validate(ct);
	}
	else if(ct.name == "location")
	{
		location_context_validate(ct);
	}
	else
	{
		cout << "invalid context" << endl;
		throw ContextException();
	}
	for(int i = 0; i < ct.subContexts.size(); i++)
		context_validate(ct.subContexts[i]);
}
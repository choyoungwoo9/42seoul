#include "Context.hpp"
#include "CustomException.hpp"

vector<string> split(string str, string del)
{
	vector<string> ret;
	
	for(int i = str.find(del); i != string::npos; i=str.find(del))
	{
		ret.push_back(str.substr(0, i));
		str.erase(0, i+del.size());
	}
	ret.push_back(str);
	return ret;
}

vector<string> white_space_split(string str) 
{
	vector<string> ret;
	int start = 0;
	int state = 0;
	for(int i = 0; i < str.size(); i ++)
	{
		if(str[i] == ' ' || str[i] == '\t')
		{
			if(state == 0)
				continue;
			if(state == 1)
			{
				ret.push_back(str.substr(start, i-start));
				state = 0;
			}
		}
		else
		{
			if(state == 0)
				start = i;
			state = 1;
		}
	}
	if(state == 1)
		ret.push_back(str.substr(start));
	return ret;
}

string string_end_trim(string str)
{
	int i;
	for(i = str.size()-1; i >= 0; i --)
	{
		if(str[i] == ' ' || str[i] == '\t')
			continue;
		else
			break;
	}
	str = str.substr(0, i+1);
	return str;
}

void server_name_check(Directive &directive)
{
	string str = string_end_trim(directive.value);
	if(str.empty())
	{
		cout << "server_name empty\n";
		throw DirectiveException();
	}
}

void client_max_body_size_check(Directive &directive)
{
	string str = string_end_trim(directive.value);
	if(str.empty())
	{
		cout << "client_max_body_size empty\n";
		throw DirectiveException();
	}
	for(int i = 0; i < str.size(); i ++)
	{
		if(str[i] == ' ' || str[i] == '\t')
		{
			cout << "client_max_body_size\n";
			throw DirectiveException();
		}
	}
	for(int i = 0; i < str.size()-1; i++)
	{
		if(str[i] < '0' || str[i] > '9')
		{
			cout << "client_max_body_size\n";
			throw DirectiveException();
		}
	}
	string tmp = "0123456789MKGmkg";
	for(int i = 0; i < tmp.size(); i ++)
	{
		if(str[str.size()-1] == tmp[i])
			return ;
	}
	cout << "client_max_body_size\n";
	throw DirectiveException();
}

void root_check(Directive &directive)
{
	string str = string_end_trim(directive.value);
	if(str.empty())
	{
		cout << "root empty\n";
		throw DirectiveException();
	}
	for(int i = 0; i < str.size(); i ++)
	{
		if(str[i] == ' ' || str[i] == '\t')
		{
			cout << "root\n";
			throw DirectiveException();
		}
	}
}

void error_page_check(Directive &directive)
{
	vector<string> vt = white_space_split(directive.value);
	if(vt.size() < 2)
	{
		cout << "error_page need more value\n";
		throw DirectiveException();
	}
	for(int i = 0; i < vt.size()-1; i ++)
	{
		for(int j = 0; j < vt[i].size(); j++)
		{
			if(vt[i][j] < '0' || vt[i][j] > '9')
			{
				cout << "error_page error code need numeric arg\n";
				throw DirectiveException();
			}
			if(atoi(vt[i].c_str()) < 300 || atoi(vt[i].c_str()) > 599)
			{
				cout << "error_page error code need between 300 and 599 value\n";
				throw DirectiveException();
			}
		}
	}
}

void listen_check(Directive &directive)
{
	string str = string_end_trim(directive.value);
	if(str.empty())
	{
		cout << "listen empty\n";
		throw DirectiveException();
	}
	for(int i = 0; i < str.size(); i ++)
	{
		if(str[i] == ' ' || str[i] == '\t')
		{
			cout << "listen need one value\n";
			throw DirectiveException();
		}
	}
	vector<string> vt = split(str, ":");
	// 65535
	for(int i = 0; i < vt.size(); i++)
	{
		if(vt[i].empty())
		{
			cout << vt[i] << endl;
			cout << "listen invalid value\n";
			throw DirectiveException();
		}
	}

	if(vt.size() == 1) //listen 8000 case
	{
		if(vt[0][0] < '0' || vt[0][0] > '9')
		{
			if(vt[0] != "localhost") //listen localhost case
			{
				cout << "listen invalid value\n";
				throw DirectiveException();
			}
		}
		else if(vt[0].find(".") != string::npos)
		{
			vector<string> ipaddr = split(vt[0], "."); //listen 127.0.0.1
			if(ipaddr.size() != 4)
			{
				cout << "listen invalid value\n";
				throw DirectiveException();
			}
			for(int i = 0; i < ipaddr.size(); i++)
			{
				if(ipaddr[i].empty())
				{
					cout << "listen invalid value\n";
					throw DirectiveException();
				}
				for(int j = 0; j < ipaddr[i].size(); j++)
				{
					if(ipaddr[i][j] < '0' || ipaddr[i][j] > '9')
					{
						cout << "listen invalid value\n";
						throw DirectiveException();
					}
				}
				
				if(atoi(ipaddr[i].c_str()) < 0 || atoi(ipaddr[i].c_str()) > 255)
				{
					cout << "listen invalid value\n";
					throw DirectiveException();
				}
			}
		}
		else //listen 8000 case
		{
			for(int i = 0; i < vt[0].size(); i++)
			{
				if(vt[0][i] < '0' || vt[0][i] > '9')
				{
					cout << "listen invalid value\n";
					throw DirectiveException();
				}
			}
			if(atoi(vt[0].c_str()) > 65535)
			{
				cout << "listen invalid value\n";
				throw DirectiveException();
			}
		}
	}
	else if(vt.size() == 2) //listen 127.0.0.1:8000 case
	{
		if(vt[0][0] < '0' || vt[0][0] > '9')
		{
			if(vt[0] != "localhost") //listen localhost:8000 case
			{
				cout << "listen invalid value\n";
				throw DirectiveException();
			}
		}
		else
		{
			vector<string> ipaddr = split(vt[0], ".");
			if(ipaddr.size() != 4)
			{
				cout << "listen invalid value\n";
				throw DirectiveException();
			}
			for(int i = 0; i < ipaddr.size(); i++)
			{
				if(ipaddr[i].empty())
				{
					cout << "listen invalid value\n";
					throw DirectiveException();
				}
				for(int j = 0; j < ipaddr[i].size(); j++)
				{
					if(ipaddr[i][j] < '0' || ipaddr[i][j] > '9')
					{
						cout << "listen invalid value\n";
						throw DirectiveException();
					}
				}
				
				if(atoi(ipaddr[i].c_str()) < 0 || atoi(ipaddr[i].c_str()) > 255)
				{
					cout << "listen invalid value\n";
					throw DirectiveException();
				}
			}
		}

		for(int i = 0; i < vt[1].size(); i++)
		{
			if(vt[1][i] < '0' || vt[1][i] > '9')
			{
				cout << "listen invalid value\n";
				throw DirectiveException();
			}
		}
		if(atoi(vt[1].c_str()) > 65535)
		{
			cout << "listen invalid value\n";
			throw DirectiveException();
		}
	}
	else
	{
		cout << "listen invalid value\n";
		throw DirectiveException();
	}
}

void autoindex_check(Directive &directive)
{
	string str = string_end_trim(directive.value);
	if(str != "on" && str != "off")
	{
		cout << "autoindex must be on or off\n";
		throw DirectiveException();
	}
}

void index_check(Directive &directive)
{
	string str = string_end_trim(directive.value);
	if(str.empty())
	{
		cout << "index empty\n";
		throw DirectiveException();
	}
}

//need implement
void fastcgi_pass_check(Directive &directive)
{
	
}

//need implement
void fastcgi_param_check(Directive &directive)
{
	
}

void check_directive(Directive &directive)
{
	if(directive.name == "server_name")
		server_name_check(directive);
	if(directive.name == "client_max_body_size")
		client_max_body_size_check(directive);
	if(directive.name == "root")
		root_check(directive);
	if(directive.name == "error_page")
		error_page_check(directive);
	if(directive.name == "listen")
		listen_check(directive);
	if(directive.name == "autoindex")
		autoindex_check(directive);
	if(directive.name == "index")
		index_check(directive);
	if(directive.name == "fastcgi_pass")
		fastcgi_pass_check(directive);
	if(directive.name == "fastcgi_param")
		fastcgi_param_check(directive);
}

void directive_validate(Context &ct)
{
	for(int i = 0; i < ct.directives.size(); i ++)
	{
		check_directive(ct.directives[i]);
	}
	for(int i = 0; i < ct.subContexts.size(); i ++)
		directive_validate(ct.subContexts[i]);
}
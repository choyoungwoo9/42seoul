#include "Context.hpp"

Context::Context(string name, string str)
{
	this->name = name;
	parse_conf(str);
	main_flag = 0;
}

Context::Context(string name, string str, int main_flag)
{
	this->name = name;
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

//white space를 밀고 다음 단어 가져옴
string Context::get_key(int &i, string &str){
	while(str[i] == '\n' || str[i] == ' ' || str[i] == '\t')
		i ++;
	int start = i;
	for(; i < str.size(); i ++)
	{
		//directive규칙을 소문자라고 임의로 정했음(확인필요)
		//add under bar 
		if(!islower(str[i]) && str[i] != '_')
		{
			if(i == start)
			{
				cout << "key" << endl;
				throw ParseException();
			}
			break;
		}
	}
	return str.substr(start, i-start);
}

int Context::is_context(string &str){
	if(str == "http" || str == "events" || str == "server" || str == "location"){
		return 1;
	}
	return 0;
}

string Context::get_bracket(int &i, string &str)
{
	int start_idx = -1;
	int end_idx = -1;
	int cnt = 0;
	for(; i < str.size(); i ++)
	{
		if(str[i] == '{')
		{
			if(start_idx == -1)
				start_idx = i;
			cnt ++;
		}
		else if(str[i] == '}') //실패 예외처리 안되어있음
		{
			cnt --;
			if(cnt == 0)
			{
				end_idx = i;
				i ++;
				return str.substr(start_idx+1, end_idx - start_idx-1);
			}
		}
	}
	cout << "bracket" << endl;
	throw ParseException();
}

string Context::get_value(int &i, string &str){
	while(str[i] == '\n' || str[i] == ' ' || str[i] == '\t')
		i ++;
	int start = i;
	int end = 0;
	for(; i < str.size(); i ++)
	{
		if(str[i] == ';')
		{
			end = i;
			break;
		}
	}
	i ++;
	return str.substr(start, end-start);
}

string Context::get_uri(int &i, string &str)
{
	while(str[i] == '\n' || str[i] == ' ' || str[i] == '\t')
		i ++;
	int start = i;
	int end = 0;
	for(; i < str.size(); i ++)
	{
		if(str[i] == '{' || str[i] == '\n' || str[i] == ' ' || str[i] == '\t')
		{
			end = i;
			return str.substr(start, end-start);
		}
	}
	cout << "uri" << endl;
	throw ParseException();
}

void Context::parse_conf(string &str){
	// cout << "///" << name << "///" << str << "///";
	for(int i = 0; i < str.size();)
	{
		string word = get_key(i, str);
		if(word.empty())
			continue;
		else if(is_context(word)){
			string uri;
			if(word == "location")
				uri = get_uri(i, str);
			string subContextString = get_bracket(i, str);
			if(uri.empty())
				subContexts.push_back(Context(word, subContextString));
			else
			{
				subContexts.push_back(Context(word, subContextString, uri));
			}
		}
		else{ //directive일때
			string value = get_value(i, str);
			parsed_directives.push_back(ParsedDirective(word, value));
		}
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

#include "Context.hpp"

//white space를 밀고 다음 단어 가져옴
static string get_key(int &i, string &str){
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

static int is_context(string &str){
	if(str == "http" || str == "events" || str == "server" || str == "location"){
		return 1;
	}
	return 0;
}

static string get_bracket(int &i, string &str)
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

static string get_value(int &i, string &str){
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

static string get_uri(int &i, string &str)
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
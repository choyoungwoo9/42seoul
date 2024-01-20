#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string whitespaceList = " \n\t";
string syntaxStringList = "{};";

bool isWhiteSpace(char ch)
{
	return whitespaceList.find(ch) != string::npos;
}
bool isSyntaxString(char ch)
{
	return syntaxStringList.find(ch) != string::npos;
}

vector<string> tokenizer(string str)
{
	vector<string> tokenList;
	for (int i = 0; i < str.length(); i++)
	{
		if (isWhiteSpace(str[i]))
			continue;
		if (isSyntaxString(str[i]))
		{
			tokenList.push_back(str.substr(i, 1));
			continue;
		}
		int endIndex = i + 1;
		for (;; endIndex++)
		{
			if (endIndex >= str.length() || isWhiteSpace(str[endIndex]) || isSyntaxString(str[endIndex]))
				break;
		}
		tokenList.push_back(str.substr(i, endIndex - i));
		i = endIndex - 1;
	}
	return tokenList;
}

vector<string> contextList = {"events", "http", "server", "location"};
vector<string> directiveList = {"client_max_body_size", "server_name", "root", "error_page", "listen", "autoindex", "index", "fastcgi_pass", "fastcgi_param"};

bool isContext(string &token)
{
	return find(contextList.begin(), contextList.end(), token) != contextList.end();
}

bool isDirective(string &token)
{
	return find(directiveList.begin(), directiveList.end(), token) != directiveList.end();
}

class Directive
{
public:
	string type;
	vector<string> valueList;
};

class Context
{
public:
	string type;
	vector<string> valueList;
	vector<Context> subContext;
	vector<Directive> directiveList;
};

void exceptionWithMsg(string msg)
{
	cerr << msg << endl;
	throw new exception();
}

// directive라는것을 알고 있을때 directive의 이름을 설정하고 다음 토큰으로 들어옴
void directiveParse(Directive &directive, vector<string> &tokens, int &tokenIndex)
{
	for (; tokenIndex < tokens.size(); tokenIndex++)
	{
		if (tokens[tokenIndex].compare(";") == 0)
		{
			tokenIndex++;
			return;
		}
		directive.valueList.push_back(tokens[tokenIndex]);
	}
	exceptionWithMsg("Not Have semi colon ;");
}

// context라는것을 알고 있을때 context의 이름을 설정하고 다음 토큰으로 들어옴
void contextParse(Context &context, vector<string> &tokens, int &tokenIndex)
{
	// cout << "current Token : " << tokens[tokenIndex] << endl;
	cout << "context : " << context.type << endl;
	// location 컨텍스트는 값 가지고 있음
	if (context.type == "location")
		context.valueList.push_back(tokens[tokenIndex++]);
	// 아직 끝나면 안됨
	if (tokenIndex == tokens.size())
		exceptionWithMsg("early end");
	// main 컨텍스트는 중괄호 없다
	if (context.type != "main" && tokens[tokenIndex++].compare("{") != 0)
		exceptionWithMsg("MUST have left brace {");
	for (; tokenIndex < tokens.size();)
	{
		cout << "tokenIndex : " << tokenIndex << endl;
		cout << "current Token : " << tokens[tokenIndex] << endl;
		if (tokens[tokenIndex].compare("}") == 0)
		{
			tokenIndex ++;
			if (context.type == "main")
				exceptionWithMsg("main MUST not have right brace }");
			return;
		}
		if (isContext(tokens[tokenIndex]))
		{
			Context subContext;
			subContext.type = tokens[tokenIndex];
			context.subContext.push_back(subContext);
			tokenIndex++;
			contextParse(subContext, tokens, tokenIndex);
		}
		else if (isDirective(tokens[tokenIndex]))
		{
			cout << "here " << tokens[tokenIndex] << endl;
			Directive subDirective;
			subDirective.type = tokens[tokenIndex];
			context.directiveList.push_back(subDirective);
			tokenIndex++;
			directiveParse(subDirective, tokens, tokenIndex);
		}
		else
		{
			cout << "token : " << tokens[tokenIndex] << endl;
			exceptionWithMsg("Not Reserved Word");
		}
	}
	if (context.type != "main")
		exceptionWithMsg("MUST have right brace {");
	return;
}

// 파싱에서는 파싱에 관련된 규칙들 {}, ; 같은것 잘 지켰는지를 확인
// Context 트리형태로 파싱
Context parser(vector<string> &tokens)
{
	Context mainContext;
	mainContext.type = "main";
	int i = 0;
	contextParse(mainContext, tokens, i);
	return mainContext;
}

void printDepth(int depth)
{
	for (int i = 0; i < depth; i++)
		cout << "\t";
}

void contextPrint(int depth, Context &context)
{
	printDepth(depth);
	cout << "contextPrintStart" << endl;
	printDepth(depth);
	cout << "type : " << context.type << endl;
	printDepth(depth);
	if(context.valueList.size())
		cout << "value Print" << endl;
	for(int i = 0; i < context.valueList.size(); i++)
	{
		printDepth(depth);
		cout << context.valueList[i] << endl;
	}
	printDepth(depth);
	if(context.directiveList.size())
		cout << "directive Print" << endl;
	for(int i = 0; i < context.directiveList.size();i++)
	{
		printDepth(depth);
		cout << "directive type : " << context.directiveList[i].type << endl;
		cout << "directive Value Print : ";
		for(int j = 0; j < context.directiveList[i].valueList.size(); j++)
		{
			cout << context.directiveList[i].valueList[j] << " ";
		}
		cout << endl;
	}
	if(context.subContext.size())
		cout << "subContext Print" << endl;
	for(int i = 0; i < context.subContext.size();i++)
	{
		contextPrint(depth+1, context.subContext[i]);
	}
	cout << endl;
}

int main()
{
	int fd = open("config", O_RDONLY);
	char buf[10000];
	int length = read(fd, buf, sizeof(buf));
	buf[length] = '\0';
	// cout << buf << endl;
	vector<string> tokens = tokenizer(buf);
	// for (int i = 0; i < tokens.size(); i++)
	// 	cout << tokens[i] << endl;
	Context mainContext = parser(tokens);

	// cout << "print Start!!!!!!!!!\n" << endl;
	// contextPrint(0, mainContext);
}
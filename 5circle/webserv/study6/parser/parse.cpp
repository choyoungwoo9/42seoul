#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "parseContext.hpp"


std::vector<std::string> contextList = {"events", "http", "server", "location"};
std::vector<std::string> directiveList = {"client_max_body_size", "server_name", "root", "error_page", "listen", "autoindex", "index", "fastcgi_pass", "fastcgi_param"};

bool isContext(std::string &token)
{
	return find(contextList.begin(), contextList.end(), token) != contextList.end();
}

bool isDirective(std::string &token)
{
	return find(directiveList.begin(), directiveList.end(), token) != directiveList.end();
}

// directive라는것을 알고 있을때 directive의 이름을 설정하고 이 함수로 들어옴
void directiveParse(ParsedDirective &directive, std::vector<std::string> &tokens, int &tokenIndex)
{
	for (; tokenIndex < tokens.size(); tokenIndex++)
	{
		if (tokens[tokenIndex].compare(";") == 0)
		{
			tokenIndex++;
			return;
		}
		// cout << "directive value here!!!!!!!! : " << tokens[tokenIndex] << endl;
		directive.valueList.push_back(tokens[tokenIndex]);
	}
	exceptionWithMsg("Not Have semi colon ;");
}

// context라는것을 알고 있을때 context의 이름을 설정하고 이 함수로 들어옴
void contextParse(ParsedContext &context, std::vector<std::string> &tokens, int &tokenIndex)
{
	// cout << "current Token : " << tokens[tokenIndex] << endl;
	// cout << "context : " << context.type << endl;
	// location 컨텍스트는 값 가지고 있음
	if (context.type == "location")
		context.valueList.push_back(tokens[tokenIndex++]);
	// 아직 끝나면 안됨
	if (tokenIndex == tokens.size())
		exceptionWithMsg("early end");
	// 본격적으로 {}안의 내용을 파싱함
	if (context.type != "main" && tokens[tokenIndex++].compare("{") != 0)
		exceptionWithMsg("MUST have left brace {");
	for (; tokenIndex < tokens.size();)
	{
		// main 컨텍스트는 중괄호 없다
		if (tokens[tokenIndex].compare("}") == 0)
		{
			tokenIndex++;
			if (context.type == "main")
				exceptionWithMsg("main MUST not have right brace }");
			return;
		}
		else if (isContext(tokens[tokenIndex]))
		{
			ParsedContext subContext;
			subContext.type = tokens[tokenIndex];
			tokenIndex++;
			contextParse(subContext, tokens, tokenIndex);
			context.subContext.push_back(subContext);
		}
		else if (isDirective(tokens[tokenIndex]))
		{
			ParsedDirective subDirective;
			subDirective.type = tokens[tokenIndex];
			tokenIndex++;
			directiveParse(subDirective, tokens, tokenIndex);
			context.directiveList.push_back(subDirective);
		}
		else
		{
			std::cout << tokens[tokenIndex];
			exceptionWithMsg(" : Not Reserved Word");
		}
	}
	if (context.type != "main")
		exceptionWithMsg("MUST have right brace {");
	return;
}

// void validateDirective()
// {
// 	// validateDirectiveInContext
// }

void validateMainContextRules(ParsedContext &mainContext)
{
	bool eventFlag = false;
	bool httpFlag = false;
	for (int i = 0; i < mainContext.subContext.size(); i++)
	{
		if (mainContext.subContext[i].type == "events")
			eventFlag = true;
		if (mainContext.subContext[i].type == "http")
			httpFlag = true;
	}
	if (mainContext.subContext.size() != 2 || !eventFlag || !httpFlag)
		exceptionWithMsg("mainContext must contain event and http context");
}

void validateUniqueDirective(std::vector<ParsedDirective> directiveList)
{
	int maxBodyCount = 0;
	int rootCount = 0;
	int autoIndexCount = 0;
	for(int i = 0; i < directiveList.size(); i++)
	{
		if(directiveList[i].type == "client_max_body_size")
			maxBodyCount ++;
		else if(directiveList[i].type == "root")
			rootCount ++;
		else if(directiveList[i].type == "autoindex")
			autoIndexCount ++;
	}
	if(maxBodyCount > 2 || rootCount > 2 || autoIndexCount > 2)
		exceptionWithMsg("unique directive is not unique");
}

void validateContext(ParsedContext &context)
{
	//main context일때 자식이 events, http만 가질 수 있는 것 확인
	if (context.type == "main")
		validateMainContextRules(context);
	//부모 컨텍스트, 자식컨텍스트 확인
	for (int i = 0; i < context.subContext.size(); i++)
		validateChildContextInParrentContext(context.type, context.subContext[i].type);
	for (int i = 0; i < context.directiveList.size(); i++)
	{
		//부모 컨텍스트, 자식 디렉티브 확인
		validateDirectiveInContext(context.type, context.directiveList[i].type);
		//자식 디렉티브 밸류 확인
		validateDirectiveValueList(context.directiveList[i]);
	}
	//unique한 directive 실제로 고유한지 유효성검사
	validateUniqueDirective(context.directiveList);
}

void validateParseTree(ParsedContext &mainContext)
{
	validateContext(mainContext);
}

// 파싱에서는 파싱에 관련된 규칙들 {}, ; 같은것 잘 지켰는지를 확인
// Context 트리형태로 파싱
ParsedContext parse(std::vector<std::string> &tokens)
{
	ParsedContext mainContext;
	mainContext.type = "main";
	int i = 0;
	contextParse(mainContext, tokens, i);
	validateParseTree(mainContext);
	return mainContext;
}
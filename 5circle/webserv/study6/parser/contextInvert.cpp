#include "parseContext.hpp"

void mapDirective(Context &context, ParsedDirective &parsedDirective)
{
	if (parsedDirective.type == DIRECTIVE_CLIENT_MAX_BODY_SIZE)
	{
		// context에 해당하는 directive임을 명시
		context.clientMaxSizeD.isValid = true;
		// 실제 밸류 집어넣는 로직
		//  context.clientMaxSizeD.~~
	}
	else if (parsedDirective.type == DIRECTIVE_LISTEN)
	{
		int idx = parsedDirective.valueList[0].find(":");
		context.listenD.host = parsedDirective.valueList[0].substr(0, idx);
		// 추후 stoi 변경 - cpp 11
		context.listenD.port = stoi(parsedDirective.valueList[0].substr(idx + 1));
		context.listenD.isValid = true;
	}
	else if (parsedDirective.type == DIRECTIVE_SERVER_NAME)
	{
		context.serverNameD.isValid = true;
		std::vector<std::string> newVector;
		context.serverNameD.serverNameVector = newVector;
		for (int i = 0; i < parsedDirective.valueList.size(); i++)
			context.serverNameD.serverNameVector.push_back(parsedDirective.valueList[i]);
	}
	else if (parsedDirective.type == DIRECTIVE_ROOT)
	{
		context.rootD.isValid = true;
		context.rootD.path = parsedDirective.valueList[0];
	}
	else if (parsedDirective.type == DIRECTIVE_ERROR_PAGE)
	{
		// 301 302 .. path 이런 형식만 유효한것으로 간주
		//  에러페이지 추후 생각
		context.errorPageD.isValid = true;
	}
	else if (parsedDirective.type == DIRECTIVE_AUTOINDEX)
	{
		context.autoIndexD.isValid = true;
		if (parsedDirective.valueList[0].compare("on") == 0)
			context.autoIndexD.isAutoIndexOn = true;
		else
			context.autoIndexD.isAutoIndexOn = false;
	}
	else if (parsedDirective.type == DIRECTIVE_INDEX)
	{
		context.indexD.isValid = true;
		std::vector<std::string> newVector;
		context.indexD.fileVector = newVector;
		for (int i = 0; i < parsedDirective.valueList.size(); i++)
			context.indexD.fileVector.push_back(parsedDirective.valueList[i]);
	}
	else if (parsedDirective.type == DIRECTIVE_RETURN)
	{
		context.returnD.isValid = true;
		// 일단은 리다이렉트만 생각함
		// 추후 text 활용하는것 고려
		//  추후 stoi 변경 - cpp 11
		context.returnD.statusCode = stoi(parsedDirective.valueList[0]);
		context.returnD.URL = stoi(parsedDirective.valueList[1]);
	}
}

// mainContext를 시작으로 컨텍스트 돌면서 재귀적으로 판단
void contextLoop(Context &context, ParsedContext &parsedContext)
{
	for (int i = 0; i < parsedContext.directiveList.size(); i++)
		mapDirective(context, parsedContext.directiveList[i]);

	for (int i = 0; i < parsedContext.subContext.size(); i++)
	{
		// std::cout << "type : " << context.type << std::endl;
		// 속성 복사
		Context subContext;
		// 현재 컨텍스트의 서브 컨텍스트로 추가
		// if (context.subContextVector.size() != 0)
		// {
		// 	std::cout << context.subContextVector[0].subContextVector.size() << std::endl;
		// }
		context.subContextVector.push_back(subContext);
		// if (context.subContextVector.size() != 0)
		// {
		// 	std::cout << context.subContextVector[0].subContextVector.size() << std::endl;
		// }
		// 타입 할당
		context.subContextVector[i].type = parsedContext.subContext[i].type;
		// cout <<"print !!!!!!!!!!! " << parsedContext.subContext[i].type << endl;
		// location 고려 밸류 리스트 복사
		// 생성자에 넣는것 추후 추가
		context.subContextVector[i].valueList = parsedContext.subContext[i].valueList;
		context.subContextVector[i].directiveCopy(context);
		// 서브 컨텍스트의 속성검사
		contextLoop(context.subContextVector[i], parsedContext.subContext[i]);
	}
}

void parseTreeToContextTree(Context &mainContext, ParsedContext &parsedMainContext)
{
	mainContext.type = CONTEXT_MAIN;
	contextLoop(mainContext, parsedMainContext);
	validateDuplicateServerName(mainContext);
	// cout << mainContext.subContextVector[1].type << endl;
	// cout << mainContext.subContextVector[1].subContextVector[0].type << endl;
	// cout << mainContext.subContextVector[1].subContextVector[0].subContextVector[0].type << endl;
	// cout << "|||||||||" << endl;
}
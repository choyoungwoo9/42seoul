#include "parseContext.hpp"

static bool isStatusCode(std::string value)
{
	return true;
}

static bool isPort(std::string value)
{
	return true;
}

static bool isIp(std::string value)
{
	return true;
}

static void validateDirectiveServerName(ParsedDirective &directive)
{
	if (directive.valueList.size() == 0)
	{
		std::cerr << "server_name value error" << std::endl;
		throw new std::exception();
	}
}

static void validateDirectiveClientMaxBodySize(ParsedDirective &directive)
{
	// if(directive.valueList.size() == 0)
	// {
	// 	std::cerr << "server_name value error" << std::endl;
	// 	throw new exception();
	// }
}

static void validateDirectiveRoot(ParsedDirective &directive)
{
	if (directive.valueList.size() != 1)
		exceptionWithMsg("root value error");
}

static void validateDirectiveErrorPage(ParsedDirective &directive)
{
	if (directive.valueList.size() < 2)
		exceptionWithMsg("error_page value error");
	for (int i = 0; i < directive.valueList.size() - 1; i++)
	{
		if (!isStatusCode(directive.valueList[i]))
			exceptionWithMsg("error_page value error");
	}
}

static void validateDirectiveListen(ParsedDirective &directive)
{
	if (directive.valueList.size() != 1)
		exceptionWithMsg("listen value error");
	// 127.0.0.1:80 이런거 테스트 해야함
	// host, port 테스트
	int idx = directive.valueList[0].find(':');
	if(idx == std::string::npos || !isIp(directive.valueList[0].substr(0, idx)) || !isPort(directive.valueList[0].substr(idx+1)))
		exceptionWithMsg("listen value error");
}

static void validateDirectiveAutoIndex(ParsedDirective &directive)
{
	if (directive.valueList.size() != 1)
		exceptionWithMsg("autoindex value error");
	if (directive.valueList[0].compare("on") != 0 && directive.valueList[0].compare("off") != 0)
		exceptionWithMsg("autoindex value error");
}

static void validateDirectiveIndex(ParsedDirective &directive)
{
	if (directive.valueList.size() == 0)
		exceptionWithMsg("index value error");
}

static void validateDirectiveReturn(ParsedDirective &directive)
{
	if (directive.valueList.size() == 0 || directive.valueList.size() > 2)
		exceptionWithMsg("return error");
	if (directive.valueList.size() == 1 && isStatusCode(directive.valueList[0]))
		exceptionWithMsg("return error");
}

static void validateDirectiveFastCgiPass(ParsedDirective &directive)
{
	// if(directive.valueList.size() != 1)
	// {
	// 	std::cerr << "root value error" << std::endl;
	// 	throw new exception();
	// }
}

static void validateDirectiveFastCgiParam(ParsedDirective &directive)
{
	// if(directive.valueList.size() != 1)
	// {
	// 	std::cerr << "root value error" << std::endl;
	// 	throw new exception();
	// }
}

void validateDirectiveValueList(ParsedDirective &directive)
{
	if (directive.type == "server_name")
	{
		validateDirectiveServerName(directive);
	}
	else if (directive.type == "client_max_body_size")
	{
		validateDirectiveClientMaxBodySize(directive);
	}
	else if (directive.type == "root")
	{
		validateDirectiveRoot(directive);
	}
	else if (directive.type == "error_page")
	{
		validateDirectiveErrorPage(directive);
	}
	else if (directive.type == "listen")
	{
		validateDirectiveListen(directive);
	}
	else if (directive.type == "autoindex")
	{
		validateDirectiveAutoIndex(directive);
	}
	else if (directive.type == "index")
	{
		validateDirectiveIndex(directive);
	}
	else if (directive.type == "fastcgi_pass")
	{
		validateDirectiveFastCgiPass(directive);
	}
	else if (directive.type == "fastcgi_param")
	{
		validateDirectiveFastCgiParam(directive);
	}
	else if (directive.type == "return")
	{
		validateDirectiveReturn(directive);
	}
}


static void validateDuplicateServerNameInHttpContext(Context &httpContext)
{
	// hostName+port, serverName을 의미함
	std::set<std::string> storage;
	//server Loop
	for (int i = 0; i < httpContext.subContextVector.size(); i++)
	{
		std::string host = httpContext.subContextVector[i].listenD.host;
		int port = httpContext.subContextVector[i].listenD.port;
		//serverName Loop
		for (int j = 0; j < httpContext.subContextVector[i].serverNameD.serverNameVector.size(); j++)
		{
			std::string identifier = host + std::to_string(port) + httpContext.subContextVector[i].serverNameD.serverNameVector[j];
			if(storage.find(identifier) !=  storage.end())
				exceptionWithMsg("duplicate serverName");
			storage.insert(identifier);
		}
	}
}

void validateDuplicateServerName(Context &mainContext)
{
	for (int i = 0; i < mainContext.subContextVector.size(); i++)
	{
		if (mainContext.subContextVector[i].type.compare(CONTEXT_HTTP) == 0)
			validateDuplicateServerNameInHttpContext(mainContext.subContextVector[i]);
	}
}
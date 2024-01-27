#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "parseContext.hpp"

static void printDepth(int depth)
{
	for (int i = 0; i < depth; i++)
		std::cout << "\t";
}

void parseTreePrint(int depth, ParsedContext &context)
{
	printDepth(depth);
	std::cout << "contextPrintStart" << std::endl;
	printDepth(depth);
	std::cout << "type : " << context.type << std::endl;
	if (context.valueList.size())
	{
		printDepth(depth);
		std::cout << "value Print" << std::endl;
	}
	for (int i = 0; i < context.valueList.size(); i++)
	{
		printDepth(depth);
		std::cout << context.valueList[i] << std::endl;
	}
	if (context.directiveList.size())
	{
		printDepth(depth);
		std::cout << "directive Print" << std::endl;
	}
	for (int i = 0; i < context.directiveList.size(); i++)
	{
		printDepth(depth);
		std::cout << "directive type : " << context.directiveList[i].type;
		std::cout << " ||||| ValueList Print : ";
		for (int j = 0; j < context.directiveList[i].valueList.size(); j++)
		{
			std::cout << context.directiveList[i].valueList[j] << " ";
		}
		std::cout << std::endl;
	}
	for (int i = 0; i < context.subContext.size(); i++)
	{
		parseTreePrint(depth + 1, context.subContext[i]);
	}
	std::cout << std::endl;
}

void directivePrint(int depth, Context &context)
{
	std::cout << std::endl;
	printDepth(depth);
	std::cout << "directive Print" << std::endl;
	if (context.clientMaxSizeD.isValid)
	{
		printDepth(depth);
		std::cout << "clientMaxSize" << std::endl;
	}
	if (context.listenD.isValid)
	{
		printDepth(depth);
		std::cout << "listenD" << std::endl;
		printDepth(depth);
		std::cout << "host : " << context.listenD.host << " port : " << context.listenD.port << std::endl;
	}
	if (context.serverNameD.isValid)
	{
		printDepth(depth);
		std::cout << "serverNameD" << std::endl;
		printDepth(depth);
		for (int i = 0; i < context.serverNameD.serverNameVector.size(); i++)
			std::cout << "||" << context.serverNameD.serverNameVector[i];
		std::cout << std::endl;
	}
	if (context.rootD.isValid)
	{
		printDepth(depth);
		std::cout << "rootD" << std::endl;
		printDepth(depth);
		std::cout << context.rootD.path << std::endl;
	}
	if (context.errorPageD.isValid)
	{
		printDepth(depth);
		std::cout << "errorPageD" << std::endl;
		printDepth(depth);
		std::cout << "statusCode" << context.errorPageD.URL << std::endl;
		for (int i = 0; i < context.errorPageD.statusCodeVector.size(); i++)
			std::cout << "||" << context.errorPageD.statusCodeVector[i] << std::endl;
		std::cout << std::endl;
		printDepth(depth);
		std::cout << "URL : " << context.errorPageD.URL << std::endl;
	}
	if (context.autoIndexD.isValid)
	{
		printDepth(depth);
		std::cout << "autoIndexD" << std::endl;
		printDepth(depth);
		std::cout << std::boolalpha << context.autoIndexD.isAutoIndexOn << std::endl;
	}
	if (context.indexD.isValid)
	{
		printDepth(depth);
		std::cout << "indexD" << std::endl;
		printDepth(depth);
		std::cout << "file : ";
		for (int i = 0; i < context.indexD.fileVector.size(); i++)
			std::cout << "||" << context.indexD.fileVector[i];
		std::cout << std::endl;
	}
	if (context.returnD.isValid)
	{
		printDepth(depth);
		std::cout << "returnD : " << std::endl;
		printDepth(depth);
		std::cout << "statusCode : " << context.returnD.statusCode << std::endl;
		printDepth(depth);
		std::cout << "URL : " << context.returnD.URL << std::endl;
	}
	printDepth(depth);
	std::cout << "directive end~!!!!!!" << std::endl;
	std::cout << std::endl;
}

void contextPrint(int depth, Context &context)
{
	printDepth(depth);
	std::cout << "contextPrintStart" << std::endl;
	printDepth(depth);
	std::cout << "type : " << context.type << std::endl;
	if (context.valueList.size())
	{
		printDepth(depth);
		std::cout << "value Print" << std::endl;
	}
	for (int i = 0; i < context.valueList.size(); i++)
	{
		printDepth(depth);
		std::cout << context.valueList[i] << std::endl;
	}
	directivePrint(depth, context);
	for (int i = 0; i < context.subContextVector.size(); i++)
	{
		contextPrint(depth + 1, context.subContextVector[i]);
	}
	std::cout << std::endl;
}
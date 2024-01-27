#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>


#include "../nginxConfig.hpp"

//나중에 struct로 변경
class ParsedDirective
{
public:
	std::string type;
	std::vector<std::string> valueList;
};

class ParsedContext
{
public:
	std::string type;
	std::vector<std::string> valueList;
	std::vector<ParsedContext> subContext;
	std::vector<ParsedDirective> directiveList;
};

void exceptionWithMsg(std::string msg);
std::vector<std::string> tokenizer(std::string str);
ParsedContext parse(std::vector<std::string> &tokens);
void parseTreePrint(int depth, ParsedContext &context);
void exceptionWithMsg(std::string msg);
void validateDirectiveInContext(std::string &contextType, std::string &directiveType);
void validateChildContextInParrentContext(std::string &parrentContextType, std::string &childContextType);
void validateDirectiveValueList(ParsedDirective &directive);
void validateDuplicateServerName(Context &mainContext);

void parseTreeToContextTree(Context &context, ParsedContext &parsedMainContext);
void contextPrint(int depth, Context &context);
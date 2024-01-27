#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::string whitespaceList = " \n\t";
std::string syntaxStringList = "{};";

bool isWhiteSpace(char ch)
{
	return whitespaceList.find(ch) != std::string::npos;
}
bool isSyntaxString(char ch)
{
	return syntaxStringList.find(ch) != std::string::npos;
}

std::vector<std::string> tokenizer(std::string str)
{
	std::vector<std::string> tokenList;
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
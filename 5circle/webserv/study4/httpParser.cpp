#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <stdlib.h>

std::vector<std::string> split(std::string &str, std::string del)
{
	std::vector<std::string> tokens;
	int start = 0;
	int end = str.find(del);
	while (end != std::string::npos)
	{
		tokens.push_back(str.substr(start, end - start));
		start = end + del.length();
		end = str.find(del, start);
	}
	tokens.push_back(str.substr(start, end - start));
	return tokens;
}

class http
{
public:
	http()
	{
		isFileEnd = false;
		isHeadEnd = false;
		statusCode = 200;
		statusMsg = "OK";
	}
	std::string makeHeader()
	{
		std::string ret;
		ret += "HTTP/1.1 ";
		ret += std::to_string(statusCode);
		ret += " ";
		ret += statusMsg;
		ret += "\nContent-Type: text/html; charset=utf-8;\n\n";
		return ret;
	}
	void addReqMsg(std::string reqMsg)
	{
		std::string del = "\r\n\r\n";
		if (isHeadEnd)
		{
			body += reqMsg;
			return;
		}
		rawHeader += reqMsg;
		int headerEndPos = rawHeader.find(del);
		if (headerEndPos != std::string::npos)
		{
			isHeadEnd = true;
			body = rawHeader.substr(headerEndPos + del.length(), rawHeader.length() - headerEndPos - del.length());
			rawHeader = rawHeader.substr(0, headerEndPos);
			parseHead();
		}
	}

	void print()
	{
		std::cout << "method : ||" << method << "||" << std::endl;
		std::cout << "target : ||" << target << "||" << std::endl;
		std::cout << "httpVersion : ||" << httpVersion << "||" << std::endl;
		for (auto iter = headers.begin(); iter != headers.end(); iter++)
			std::cout << "||" << iter->first << "|| : ||" << iter->second << "||" << std::endl;
	};
	std::string rawHeader;
	std::string method;
	std::string target;
	std::string httpVersion;
	std::map<std::string, std::string> headers;
	std::string body;
	std::string response;
	bool isHeadEnd;
	bool isFileEnd;

	int statusCode;
	std::string statusMsg;

private:
	void parseHead()
	{
		std::string del = "\r\n";
		std::vector<std::string> splittedHeader = split(rawHeader, del);
		if (splittedHeader.size() < 2)
		{
			std::cout << "invalid Header" << std::endl;
			exit(1);
		}
		std::vector<std::string> startLine = split(splittedHeader[0], " ");
		if (startLine.size() != 3)
		{
			std::cout << "invalid startLine" << std::endl;
			exit(1);
		}
		method = startLine[0];
		target = startLine[1];
		httpVersion = startLine[2];

		for (int i = 1; i < splittedHeader.size(); i++)
		{
			if (splittedHeader[i].size() == 0)
				return;
			std::vector<std::string> splittedEntity = split(splittedHeader[i], ": ");
			if (splittedEntity.size() != 2)
			{
				std::cout << "invalid each Header" << std::endl;
				exit(1);
			}
			headers[splittedEntity[0]] = splittedEntity[1];
		}
	}
};

// //reqMSG가 이상하게 들어오는 얘외처리를 해야할까?
// //split에서 del로 끝나는 경우 마지막 요소가 ""로 끝나는 예외처리 실제로 적용되는 부분만 해 놓았음
// //일단 map으로 헤더 저장해 놓았음

// int main()
// {
// 	string example = "POST /cgi-bin/process.cgi HTTP/1.1\r\nUser-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\r\nHost: www.tutorialspoint.com\r\nContent-Type: text/xml; charset=utf-8\r\nContent-Length: length\r\nAccept-Language: en-us\r\nAccept-Encoding: gzip, deflate\r\nConnection: Keep-Alive\r\n\r\nabcd\ndasfsd\r\ndf";
// 	http httpData;
// 	httpData.addReqMsg(example);
// 	httpData.print();
// }
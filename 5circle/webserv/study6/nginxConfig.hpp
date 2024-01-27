#ifndef NGINX_CONFIG_HPP
#define NGINX_CONFIG_HPP

#include <vector>
#include <string>

const std::string CONTEXT_MAIN = "main";
const std::string CONTEXT_EVENT = "event";
const std::string CONTEXT_HTTP = "http";
const std::string CONTEXT_SERVER = "server";
const std::string CONTEXT_LOCATION = "location";
const std::string DIRECTIVE_SERVER_NAME = "server_name";
const std::string DIRECTIVE_CLIENT_MAX_BODY_SIZE = "client_max_body_size";
const std::string DIRECTIVE_ROOT = "root";
const std::string DIRECTIVE_ERROR_PAGE = "error_page";
const std::string DIRECTIVE_LISTEN = "listen";
const std::string DIRECTIVE_AUTOINDEX = "autoindex";
const std::string DIRECTIVE_INDEX = "index";
const std::string DIRECTIVE_RETURN = "return";

// 요기에는 실제로 사용하는 값 사용함
// 고로 std::string -> int 작업도 모두 처리되어있는 상태이다.
typedef struct clientMaxBodySizeDirective
{
	bool isValid;

} clientMaxBodySizeDirective;

typedef struct listenDirective
{
	bool isValid;
	// 127.0.0.1:80
	std::string host;
	int port;
} listenDirective;

typedef struct serverNameDirective
{
	bool isValid;
	std::vector<std::string> serverNameVector;
} serverNameDirective;

typedef struct rootDirective
{
	bool isValid;
	std::string path;
} rootDirective;

typedef struct errorPageDirective
{
	bool isValid;
	std::string URL;
	std::vector<int> statusCodeVector;
} errorPageDirective;

typedef struct autoindexDirective
{
	bool isValid;
	bool isAutoIndexOn;
} autoindexDirective;

typedef struct indexDirective
{
	bool isValid;
	std::vector<std::string> fileVector;
} indexDirective;

typedef struct returnDirective
{
	bool isValid;
	// 일단 301만 처리하고 추후 추가함
	int statusCode;
	std::string URL;
	std::string text;
} returnDirective;

class Context
{
public:
	// 기본 생성자
	Context()
	{
		serverNameD.isValid = true;
		serverNameD.serverNameVector.push_back("");
		clientMaxSizeD.isValid = false;
		// clientMaxSizeD.~~ 디폴트 설정
		rootD.isValid = false;
		rootD.path = "html";
		errorPageD.isValid = false;
		// 처음부터 할당되는 형태 -> 초기화 안되도 사용가능한 directive
		listenD.host = "0.0.0.0";
		listenD.port = 8000;
		listenD.isValid = true;
		autoIndexD.isValid = false;
		indexD.isValid = false;
		returnD.isValid = false;
	};
	// 복사생성자는 directive만 복사
	// Context(const Context &obj)
	// {
	// 	type = obj.type;
	// 	serverNameD = obj.serverNameD;
	// 	clientMaxSizeD = obj.clientMaxSizeD;
	// 	rootD = obj.rootD;
	// 	errorPageD = obj.errorPageD;
	// 	listenD = obj.listenD;
	// 	autoIndexD = obj.autoIndexD;
	// 	indexD = obj.indexD;
	// 	returnD = obj.returnD;
	// };
	// Context &operator=(const Context &obj)
	// {
	// 	serverNameD = obj.serverNameD;
	// 	clientMaxSizeD = obj.clientMaxSizeD;
	// 	rootD = obj.rootD;
	// 	errorPageD = obj.errorPageD;
	// 	listenD = obj.listenD;
	// 	autoIndexD = obj.autoIndexD;
	// 	indexD = obj.indexD;
	// 	returnD = obj.returnD;
	// 	return *this;
	// }
	void directiveCopy(const Context &obj)
	{
		serverNameD = obj.serverNameD;
		clientMaxSizeD = obj.clientMaxSizeD;
		rootD = obj.rootD;
		errorPageD = obj.errorPageD;
		listenD = obj.listenD;
		autoIndexD = obj.autoIndexD;
		indexD = obj.indexD;
		returnD = obj.returnD;
	}
	std::string type;
	std::vector<std::string> valueList;
	// 하위 Context
	std::vector<Context> subContextVector;
	// 없는 요소는 isValid가 0
	serverNameDirective serverNameD;
	clientMaxBodySizeDirective clientMaxSizeD;
	rootDirective rootD;
	errorPageDirective errorPageD;
	listenDirective listenD;
	autoindexDirective autoIndexD;
	indexDirective indexD;
	returnDirective returnD;
};

#endif
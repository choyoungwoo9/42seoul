// fastcgi_param  QUERY_STRING       ;
// fastcgi_param  REQUEST_METHOD     GET;
// fastcgi_param  CONTENT_TYPE       ;
// fastcgi_param  CONTENT_LENGTH     ;
// fastcgi_param  SCRIPT_NAME        /;

// fastcgi_param  REQUEST_URI        /;
// fastcgi_param  DOCUMENT_URI       /;
// fastcgi_param  DOCUMENT_ROOT      /Users/youngwch/.brew/Cellar/nginx/1.25.0/html;
// fastcgi_param  SERVER_PROTOCOL    HTTP/1.1;
// fastcgi_param  REQUEST_SCHEME     http;

// fastcgi_param  GATEWAY_INTERFACE  CGI/1.1;
// fastcgi_param  SERVER_SOFTWARE    nginx/1.25.0;
// fastcgi_param  REMOTE_ADDR        127.0.0.1;
// fastcgi_param  REMOTE_PORT        49369;
// fastcgi_param  SERVER_ADDR        127.0.0.1;

// fastcgi_param  SERVER_PORT        12345;
// fastcgi_param  SERVER_NAME        ab;
//get case

#include <iostream>
#include <cstdlib>
#include <vector>
#include <unistd.h>

using namespace std;

void set_all_env()
{
	putenv((char *)"QUERY_STRING=");
	putenv((char *)"REQUEST_METHOD=GET");
	putenv((char *)"CONTENT_TYPE=");
	putenv((char *)"CONTENT_LENGTH=");
	putenv((char *)"SCRIPT_NAME=/");

	putenv((char *)"REQUEST_URI=/hello.php");
	putenv((char *)"DOCUMENT_URI=/");
	putenv((char *)"DOCUMENT_ROOT=/Users/youngwch/.brew/Cellar/nginx/1.25.0/html");
	putenv((char *)"SERVER_PROTOCOL=HTTP/1.1");
	putenv((char *)"REQUEST_SCHEME=http");

	putenv((char *)"GATEWAY_INTERFACE=CGI/1.1");
	putenv((char *)"SERVER_SOFTWARE=nginx/1.25.0");
	putenv((char *)"REMOTE_ADDR=127.0.0.1");
	putenv((char *)"REMOTE_PORT=49369");
	putenv((char *)"SERVER_ADDR=127.0.0.1");

	putenv((char *)"SERVER_PORT=12345");
	putenv((char *)"SERVER_NAME=ab");
}

void print_404()
{
	cout << "HTTP/1.1 404 Not Found\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: 13\r\n"
            "\r\n"
            "404 Not Found";
}

void print_400()
{
    cout <<"HTTP/1.1 400 Bad Request\r\n"
			"Content-Type: text/plain\r\n"
			"Content-Length: 11\r\n"
			"\r\n"
			"Bad Request";
}

void print_501()
{
    cout << "HTTP/1.1 501 Not Implemented\r\n"
			"Content-Type: text/plain\r\n"
			"Content-Length: 15\r\n"
			"\r\n"
			"Not Implemented";
}

void print_503()
{
    cout << "HTTP/1.1 503 Service Unavailable\r\n"
			"Content-Type: text/plain\r\n"
			"Content-Length: 17\r\n"
			"\r\n"
			"Service Unavailable";
}

void check_env()
{
	vector<string> server_env = {"QUERY_STRING", "REQUEST_METHOD", "CONTENT_TYPE", "CONTENT_LENGTH", "SCRIPT_NAME",
				 "REQUEST_URI", "DOCUMENT_URI", "DOCUMENT_ROOT", "SERVER_PROTOCOL", "REQUEST_SCHEME",
				 "GATEWAY_INTERFACE", "SERVER_SOFTWARE", "REMOTE_ADDR", "REMOTE_PORT", "SERVER_ADDR",
				  "SERVER_PORT", "SERVER_NAME"};
	for(auto str : server_env)
	{
		if(getenv(str.c_str()) == NULL)
		{
			print_400();
			exit(1);
		}
	}
	return ;
}

void method_check()
{
	string method = getenv("REQUEST_METHOD");
	if(method != "GET")
	{
		print_501();
		exit(1);
	}
}

int is_file_readable(string &path) {
    // 파일 접근 권한 확인
    if (access(path.c_str(), R_OK) != 0) {
        return 0;  // 읽을 수 없는 파일
    }

    // 파일 열기 시도
    FILE* fp = fopen(path.c_str(), "r");
    if (fp == NULL) {
        return 0;
    }

    // 파일 닫기
    fclose(fp);

    return 1;  // 읽을 수 있는 파일
}

void print_file(string &body)
{

	cout << "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length:" <<
			body.size() << 
			"\r\n"
            "\r\n";
	cout << body;
}

//path를 현재위치에 할 생각
string make_path()
{
	string root = "/Users/youngwch/42/5circle/webserv/subject/solo2/php/";
	string uri = getenv("REQUEST_URI");
	if(uri.empty() || uri[0] != '/')
		return root + uri;
	else
		return root + uri.substr(1);
}

void do_cgi()
{
	//파일이 있다면 사용
	//파일이 없다면 404에러
	//하드코딩 + request_uri ?
	string path = make_path();
	if(!is_file_readable(path))
	{
		print_404();
		exit(1);
	}
	string exec_path = ("/usr/bin/php -q " + path);
	FILE *fp = popen(exec_path.c_str(), "r");
	if(fp == NULL)
	{
		print_503();
		exit(1);
	}
	string body;
	char buffer[4096];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
    	body += buffer;
    }
	pclose(fp);
	print_file(body);
}
//와야되는 환경변수가 안온경우 처리 해야하나 ?
//php GET처리하는 CGI
int main()
{
	set_all_env();
	method_check();
	// cout << getenv("REQUEST_URI") << endl;
	check_env();
	method_check();
	do_cgi();
}
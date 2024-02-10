#include <iostream>
#include <cstdlib>
#include <vector>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

void set_all_env()
{
	putenv((char *)"QUERY_STRING=");
	putenv((char *)"REQUEST_METHOD=POST");
	putenv((char *)"CONTENT_TYPE=");
	putenv((char *)"CONTENT_LENGTH=");
	putenv((char *)"SCRIPT_NAME=/");

	putenv((char *)"REQUEST_URI=/mypage");
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

void print_204()
{
	cout << "HTTP/1.1 204 No Content\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: 0\r\n"
            "\r\n";
}


void print_400()
{
    cout << "HTTP/1.1 400 Bad Request\r\n"
			"Content-Type: text/plain\r\n"
			"Content-Length: 11\r\n"
			"\r\n"
			"Bad Request";
}

void print_403()
{
	cout << "HTTP/1.1 403 Forbidden\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: 9\r\n"
            "\r\n"
            "Forbidden";
}

void print_404()
{
	cout << "HTTP/1.1 404 Not Found\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: 13\r\n"
            "\r\n"
            "404 Not Found";
}

void print_409()
{
    cout << "HTTP/1.1 409 Conflict\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: 9\r\n"
            "\r\n"
            "Conflict";
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
	if(method != "GET" && method != "POST" && method != "DELETE")
	{
		print_501();
		exit(1);
	}
}

int is_file_accessable(string &path, int option) {
    if (access(path.c_str(), option) != 0) {
        return 0;
    }
    FILE* fp = fopen(path.c_str(), "r");
    if (fp == NULL) {
        return 0;
    }

    fclose(fp);

    return 1;
}

string make_path()
{
	string root = "/Users/youngwch/42/5circle/webserv/subject/solo2/html/";
	string uri = getenv("REQUEST_URI");
	if(uri.empty() || uri[0] != '/')
		return root + uri;
	else
		return root + uri.substr(1);
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
void do_cgi_get()
{
    string path = make_path();
    if(!is_file_accessable(path, R_OK))
    {
		print_404();
		exit(1);
    }
    int fd = open(path.c_str(), O_RDONLY);
    if(fd == -1)
    {
        print_404();
        exit(1);
    }
    string body;
    char buffer[4096];
    ssize_t bytesRead;
    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
         body.append(buffer, bytesRead);
    }
    print_file(body);
    close(fd);
}

void do_cgi_post()
{
    string path = make_path();
    //파일이 있고, 쓸 권한이 없을때
    if(is_file_accessable(path, F_OK) && !is_file_accessable(path, W_OK))
    {
	    print_403();
	    exit(1);
    }
    FILE* file = fopen(path.c_str(), "w");
    if(file == NULL)
    {
        print_403();
	    exit(1);
    }

    char buffer[4096];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), stdin)) > 0) {
        size_t bytesWritten = fwrite(buffer, 1, bytesRead, file);
        if (bytesWritten != bytesRead) {
            fclose(file);
            exit(1);
        }
    }
    fclose(file);
}

void do_cgi_delete()
{
    string path = make_path();
    if(!is_file_accessable(path, F_OK))
    {
		print_404();
		exit(1);
    }
    if(remove(path.c_str()) != 0)
    {
		print_403();
		exit(1);
    }
    print_204();
}

int main()
{
	set_all_env();
	method_check();
	check_env();
	method_check();
    string method = getenv("REQUEST_METHOD");
	if(method == "GET")
    {
        do_cgi_get();
    }
    else if(method == "POST")
    {
        do_cgi_post();
    }
    else if(method == "DELETE")
    {
        do_cgi_delete();
    }
}
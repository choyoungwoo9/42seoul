
#include <vector>
#include <string>
#include <map>
using namespace std;

class requestClass
{
	public:
		requestClass();
		string httpMethod;
		string requestTarget;
		string httpVersion;
		vector<pair<string, string> > headers;
		string body;
		void appendRequest(string &rawRequest, unsigned int index);
	private:
		int level;
		int curLevelIdx;
		int headersLevel;
		void requestClass::get_body(string &rawRequest, unsigned int index);
};

requestClass::requestClass()
{
	this->level = 0;
	this->startline_level = 0;
	this->headers_level = 0;
};

void requestClass::get_headers(string &rawRequest, unsigned int index)
{
	
}

void requestClass::get_body(string &rawRequest, unsigned int index)
{
	this->body += rawRequest.substr(index, reqRequest.size()-index)
}

void requestClass::appendRequest(string &rawRequest, unsigned int index)
{
	if(level == 0)
	{
		get_startline();
	}
	if(level == 1)
	{
		get_headers();
	}
	else if(level == 2)
	{
		get_body();
	}
}

//level이 0이면 startline을 받고있는중
//level이 1이면 header을 받고있는중
//level이 2이면 body을 받고있는중
//cur_level_idx는 지금 레벨에서의 처리하고 있는 부분을 가르킴
//항상 어떤부분을 추가할때 += 로 생각하자
//한글자 한글자 읽어서 추가해도 될듯 ?
//그리고 공백을 만나면 다음 step으로 넘어가면 될듯 ?
//map으로 받고, set-cookie만 다르게 처리하자


int main()
{

}
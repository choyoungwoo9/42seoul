#include "../NginxConfig.hpp"

//추후 cgi처리 필요함 지금코드는 cgi 고려없음
bool max_body_check(sReqMsg &req, Context &server)
{
	//if req.method == host && req.ContentLength > server.config -> true
	//host인지 body인지 체크 필요함
	return req.contentLen > server.directives.client_max_body_size.size;
}
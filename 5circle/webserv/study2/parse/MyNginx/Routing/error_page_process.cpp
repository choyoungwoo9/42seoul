#include "../NginxConfig.hpp"

//호출하기 전 에러코드 세팅(res.code)하고 호출
void error_page_process(sResponseMsg &res, sReqMsg &req, Context &selected_context, Context &origin_server, int redirect_count)
{
	string err_uri = selected_context.directives.error_page.error_num[res.code];
	//절대경로
	//err_uri없는 경우는 세그먼트폴트나서 이 부분 검증 필요
	if(err_uri[0] == '/')
	{
		req.requestTarget = err_uri;
		make_response_by_server(res, req, origin_server, redirect_count+1);
	}
	else
	{
		res.code = 302;
		res.location = err_uri;
		return ;
	}
}

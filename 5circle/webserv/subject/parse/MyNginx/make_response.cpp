#include "NginxConfig.hpp"

Context &NginxConfig::find_http_context()
{
	for(int i = 0; i < mainContext.subContexts.size(); i ++)
	{
		if(mainContext.subContexts[i].name == "http")
		{
			return mainContext.subContexts[i];
		}
	}
	return mainContext;
}

Context &NginxConfig::find_server_by_full_address(string &host, string &full_address)
{
	Context &http = find_http_context();
	//http context not configured
	if(http.name == "main")
		return mainContext;
	Context *ret_context = &mainContext;
	for(int i = 0; i < http.subContexts.size(); i++)
	{
		if(http.subContexts[i].directives.listen.address != full_address)
			continue;
		if(http.subContexts[i].directives.listen.is_default_server)
			ret_context = &http.subContexts[i];
		vector<string> server_names = http.subContexts[i].directives.server_name.name_vector;
		for(int j = 0; j < server_names.size(); j++)
		{
			if(host == server_names[j])
				return http.subContexts[i];
		}
	}
	return *ret_context;
}

Context &NginxConfig::find_virtual_server(string &host, string &address, string &port)
{
	string full_address = (address + ':') + port;
	Context &ret_context = find_server_by_full_address(host, full_address);
	if(ret_context.name != "main")
		return ret_context;

	//0.0.0.0:port에서 처리해야 할 경우
	full_address = "0.0.0.0:" + port;
	ret_context = find_server_by_full_address(host, full_address);
	if(ret_context.name != "main")
		return ret_context;

	return mainContext;
}



//추후 cgi처리 필요함 지금코드는 cgi 고려없음
bool max_body_check(sReqMsg &req, Context &server)
{
	//if req.method == host && req.ContentLength > server.config -> true
	//host인지 body인지 체크 필요함
	return req.contentLen > server.directives.client_max_body_size.size;
}

void max_body_process(sResponseMsg &res, sReqMsg &req, Context &server, int redirect_count)
{
	error_page_process(res, req, server, redirect_count, 413);
}

void error_page_process(sResponseMsg &res, sReqMsg &req, Context &server, int redirect_count, int code)
{
	string err_uri = server.directives.error_page.error_num[code];
	//절대경로
	//err_uri없는 경우는 세그먼트폴트나서 이 부분 검증 필요
	if(err_uri[0] == '/')
	{
		req.requestTarget = err_uri;
		make_response_by_server(res, req, server, redirect_count+1, code);
	}
	else
	{
		res.code = 302;
		res.location = err_uri;
		return ;
	}
}

void index_process(sResponseMsg &res, sReqMsg &req, Context &server, int redirect_count)
{

}

void find_file_process(sResponseMsg &res, sReqMsg &req, Context &server, int redirect_count)
{

}


Context &find_location(string &URI, Context &server)
{
	Context *ret = &server;
	for(int i = 0; i < server.subContexts.size(); i ++)
	{
		if(URI.size() < server.subContexts[i].uri.size())
			continue;
		if(URI.substr(0, server.subContexts[i].uri.size()) != server.subContexts[i].uri)
			continue;
		if(ret != &server && ret->uri.size() > server.subContexts[i].uri.size())
			continue;
		ret = &server.subContexts[i];
	}
	if(ret != &server)
	{
		return find_location(URI, *ret);
	}
	return server;
}

void make_response_by_server(sResponseMsg &res, sReqMsg &req, Context &server, int redirect_count, int code)
{
	//현재 server와 요청 URI를 바탕으로 적절한 server골라냄
	Context &location = find_location(req.requestTarget, server);

	//500 에러 -> 내부 리다이렉션 너무 많이 한 경우
	//이경우에는 내부 리다이렉션을 너무 많이 해서 생기는것이기 때문에 다시 error_page를 찾아가지
	//않는듯 하다.
	if(redirect_count >= 10)
	{
		
		return ;
	}
	// 1. client_max_body_size고려 → 에러 페이지
	// 2. return이 있다 → return 바로 ㄱㄱ
	// 3. 만약 마지막이 /로 끝난다 → index고려
	// 4. 마지막이 /이 아니다 → 파일 찾고 그에 따른 값 반환한다.
	// 5. 에러일떄는 error page의 값을 따른다

	//첫 요청에만 max_body검사를 함 -> 이후 호출은 내부적으로 호출한것임
	if(redirect_count == 0 && max_body_check(req, server))
	{
		max_body_process(res, req, server, redirect_count);
		return ;
	}
	if(server.directives.return_d.is_set)
	{
		error_page_process(res, req, server, redirect_count, server.directives.return_d.code);
		return ;
	}
	//URI가 빈 문자열일때 있을까 ?
	//이 경우는 요청이 디렉토리인 경우
	if(req.requestTarget.size() && req.requestTarget[req.requestTarget.size()-1] == '/')
	{
		index_process(res, req, server, redirect_count);
		return ;
	}

	find_file_process(res, req, server, redirect_count);
}

sResponseMsg NginxConfig::make_response(sReqMsg &req, string &address, string &port)
{
	Context &server = find_virtual_server(req.host, address, port);
	sResponseMsg ret;
	//http컨텍스트나 server컨텍스트가 구성안된 경우를 생각한건데, 이런경우가 있을까 싶음 왜냐하면
	//구성이 안됬는데 요청이 들어오는게 이상하다.
	if(server.name == "main")
	{
		cout << "not found" << endl;
		return ret;
	}

	// cout << "print virtual server !!\n";
	// server.directives.print_all_key_value();

	//구성된 서버를 못찾은 상황인데 이런상황이 있을까 ?
	// if(server.name == "main")
	// {
	// 	return ~~;
	// }
	// server.directives

	make_response_by_server(ret, req, server, 0, 200);
	
	return ret;
}
#include "../NginxConfig.hpp"

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

void make_response_by_server(sResponseMsg &res, sReqMsg &req, Context &server, int redirect_count)
{
	//현재 server와 요청 URI를 바탕으로 적절한 server골라냄
	Context &selected_context = find_location(req.requestTarget, server);

	//500 에러 -> 내부 리다이렉션 너무 많이 한 경우
	//이경우에는 내부 리다이렉션을 너무 많이 해서 생기는것이기 때문에 다시 error_page를 찾아가지
	//않는듯 하다.
	if(redirect_count >= 10)
	{
		res.code = 500;
		getFileContents(default_500_path, res.body);
		return ;
	}
	// 1. client_max_body_size고려 → 에러 페이지
	// 2. return이 있다 → return 바로 ㄱㄱ
	// 3. 만약 마지막이 /로 끝난다 → index고려
	// 4. 마지막이 /이 아니다 → 파일 찾고 그에 따른 값 반환한다.
	// 5. 에러일떄는 error page의 값을 따른다

	//첫 요청에만 max_body검사를 함 -> 이후 호출은 내부적으로 호출한것임
	if(redirect_count == 0 && max_body_check(req, selected_context))
	{

		res.code = 413;
		error_page_process(res, req, selected_context, server, redirect_count);
		return ;
	}
	if(selected_context.directives.return_d.is_set)
	{
		res.code = selected_context.directives.return_d.code;
		return_process(res, req, selected_context ,server, redirect_count);
		return ;
	}

	//URI가 빈 문자열일때 있을까 ?
	//이 경우는 요청이 디렉토리인 경우
	if(req.requestTarget.size() && req.requestTarget[req.requestTarget.size()-1] == '/')
	{
		index_process(res, req, selected_context, server, redirect_count);
		return ;
	}

	//최종적으로 일반적인 파일 처리
	//root + URI;
	find_file_process(res, req, selected_context, server, redirect_count);
}
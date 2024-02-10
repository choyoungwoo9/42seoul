#include "../NginxConfig.hpp"

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

sResponseMsg NginxConfig::make_response(sReqMsg &req, string &address, string &port)
{
	Context &server = find_virtual_server(req.host, address, port);
	sResponseMsg ret;
	ret.code = 200;
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

	make_response_by_server(ret, req, server, 0);
	
	return ret;
}
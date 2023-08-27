#include "../NginxConfig.hpp"

bool is_redirect_code(int code)
{
	if(code == 301 || code == 302 || code == 303 || code == 307 || code == 308)
		return true;
	return false;
}

void return_process(sResponseMsg &res, sReqMsg &req, Context &selected_context, Context &origin_server, int redirect_count)
{
	if(is_redirect_code(res.code))
	{
		res.location = selected_context.directives.return_d.URI;
		return ;
	}
	else{
		res.body = selected_context.directives.return_d.URI;
		return;
	}
}

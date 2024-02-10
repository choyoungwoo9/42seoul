#include "../NginxConfig.hpp"


void find_file_process(sResponseMsg &res, sReqMsg &req, Context &selected_context, Context &origin_server, int redirect_count)
{
	cout << make_path(selected_context.directives.root.path, req.requestTarget) << endl;
	int ret_code = getFileContents(make_path(selected_context.directives.root.path, req.requestTarget), res.body);
	if(ret_code != 200)
	{
		if(res.code == 200)
		{
			res.code = ret_code;
		}
		error_page_process(res, req, selected_context, origin_server, redirect_count);
	}
}

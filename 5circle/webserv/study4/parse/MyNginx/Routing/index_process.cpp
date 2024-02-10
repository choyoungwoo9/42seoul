#include "../NginxConfig.hpp"

bool is_exist_file(string file_name)
{
	std::ifstream file(file_name.c_str());
	if (!file.is_open()) {
		return false;
    }
	file.close();
	return true;
}

void index_process(sResponseMsg &res, sReqMsg &req, Context &selected_context, Context &origin_server, int redirect_count)
{
	//autoindex 처리 필요
	string &root = selected_context.directives.root.path;
	vector<string> &index_vector = selected_context.directives.index.index_vector;
	for(int i = 0; i < index_vector.size(); i++)
	{
		if(is_exist_file(make_path(root, index_vector[i])))
		{
			cout << make_path(root, index_vector[i]) << endl;
			if(index_vector[i][0] != '/')
				req.requestTarget = '/'+index_vector[i];
			else
				req.requestTarget = index_vector[i];
			make_response_by_server(res, req, origin_server, redirect_count+1);
			return ;
		}
	}
	//못찾으면 403
	if(selected_context.directives.autoindex.state == "on")
	{
		autoindex_process(res, req, selected_context, origin_server, redirect_count);
		return ;
	}
	
	res.code = 403;
	error_page_process(res, req, selected_context, origin_server, redirect_count);
}

#include "AllDirective.hpp"


AllDirective::AllDirective()
{
}

AllDirective &AllDirective::operator =(AllDirective &param)
{
	root = param.root;
	autoindex = param.autoindex;
	listen = param.listen;
	server_name = param.server_name;
	client_max_body_size = param.client_max_body_size;
	error_page = param.error_page;
	index = param.index;
	fastcgi_pass = param.fastcgi_pass;
	fastcgi_param = param.fastcgi_param;
	return *this;
}

void AllDirective::print_all_key_value()
{
	cout << "root : " << root.path << endl;
	cout << "autoindex : " << autoindex.state << endl;
	cout << "listen : " << listen.address << endl;
	cout << "server_name : ";
	for(int i = 0; server_name.name_vector.size(); i ++)
		cout << server_name.name_vector[i] << "    ";
	cout << endl;
	cout << "client_max_body_size : " << client_max_body_size.size << endl;
	
	cout << "error_page : " << endl;
	for(map<int, string>::iterator it = error_page.error_num.begin(); it != error_page.error_num.end(); it ++)
		cout << it->first << " " << it->second << endl;
	cout << endl;

	cout << "index : " << endl;
	for(int i = 0; i < index.index_vector.size(); i ++)
		cout << index.index_vector[i] << " ";
	cout << endl;
	cout << "fastcgi_pass : " << endl;
	cout << "fastcgi_param : "  << endl;
}

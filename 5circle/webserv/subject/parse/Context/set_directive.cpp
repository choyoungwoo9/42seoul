#include "Context.hpp"

void Context::categorize_directive(ParsedDirective &parsed_directives)
{
	if(parsed_directives.name == "server_name")
		directives.server_name.set_value(parsed_directives.value);
	if(parsed_directives.name == "client_max_body_size")
		directives.client_max_body_size.set_value(parsed_directives.value);
	if(parsed_directives.name == "root")
		directives.root.set_value(parsed_directives.value);
	if(parsed_directives.name == "error_page")
		directives.error_page.set_value(parsed_directives.value);
	if(parsed_directives.name == "listen")
		directives.listen.set_value(parsed_directives.value);
	if(parsed_directives.name == "autoindex")
		directives.autoindex.set_value(parsed_directives.value);
	if(parsed_directives.name == "index")
		directives.index.set_value(parsed_directives.value);
	if(parsed_directives.name == "fastcgi_pass")
		directives.fastcgi_pass.set_value(parsed_directives.value);
	if(parsed_directives.name == "fastcgi_param")
		directives.fastcgi_param.set_value(parsed_directives.value);
	if(parsed_directives.name == "return")
		directives.return_d.set_value(parsed_directives.value);
	
}

void Context::set_directive(AllDirective parent_setting)
{
	directives = parent_setting;
	for(int i = 0; i < parsed_directives.size(); i ++)
		categorize_directive(parsed_directives[i]);

	for(int i = 0; i < subContexts.size(); i ++)
		subContexts[i].set_directive(directives);
}
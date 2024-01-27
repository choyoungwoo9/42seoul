#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

void exceptionWithMsg(std::string msg)
{
	std::cerr << msg << std::endl;
	throw new std::exception();
}

void validateDirectiveInContext(std::string &contextType, std::string &directiveType)
{
	if(directiveType == "server_name")
	{
		if(contextType != "server")
		{
			exceptionWithMsg(directiveType + " directive is Invalid in " + contextType + " context");
		}
	}
	else if(directiveType == "client_max_body_size")
	{
		if(contextType != "http" && contextType != "server" && contextType != "location")
		{
			exceptionWithMsg(directiveType + " directive is Invalid in " + contextType + " context");
		}
	}
	else if(directiveType == "root")
	{
		if(contextType != "http" && contextType != "server" && contextType != "location")
		{
			exceptionWithMsg(directiveType + " directive is Invalid in " + contextType + " context");
		}
	}
	else if(directiveType == "error_page")
	{
		if(contextType != "http" && contextType != "server" && contextType != "location")
		{
			exceptionWithMsg(directiveType + " directive is Invalid in " + contextType + " context");
		}
	}
	else if(directiveType == "listen")
	{
		if(contextType != "server")
		{
			exceptionWithMsg(directiveType + " directive is Invalid in " + contextType + " context");
		}
	}
	else if(directiveType == "autoindex")
	{
		if(contextType != "http" && contextType != "server" && contextType != "location")
		{
			exceptionWithMsg(directiveType + " directive is Invalid in " + contextType + " context");
		}
	}
	else if(directiveType == "index")
	{
		if(contextType != "http" && contextType != "server" && contextType != "location")
		{
			exceptionWithMsg(directiveType + " directive is Invalid in " + contextType + " context");
		}
	}
	else if(directiveType == "fastcgi_pass")
	{
		if(contextType != "location")
		{
			exceptionWithMsg(directiveType + " directive is Invalid in " + contextType + " context");
		}
	}
	else if(directiveType == "fastcgi_param")
	{
		if(contextType != "http" && contextType != "server" && contextType != "location")
		{
			exceptionWithMsg(directiveType + " directive is Invalid in " + contextType + " context");
		}
	}
	else if(directiveType == "return")
	{
		if(contextType != "server" && contextType != "location")
		{
			exceptionWithMsg(directiveType + " directive is Invalid in " + contextType + " context");
		}
	}
}

void validateChildContextInParrentContext(std::string &parrentContextType, std::string &childContextType)
{
	if (parrentContextType == "main")
	{
		if (childContextType != "events" && childContextType != "http")
			exceptionWithMsg(childContextType + "(child) is Invalid in " + parrentContextType + "(parrent) context");
	}
	else if (parrentContextType == "events")
	{
		exceptionWithMsg(childContextType + "(child) is Invalid in " + parrentContextType + "(parrent) context");
	}
	else if (parrentContextType == "http")
	{
		if (childContextType != "server")
			exceptionWithMsg(childContextType + "(child) is Invalid in " + parrentContextType + "(parrent) context");
	}
	else if (parrentContextType == "server")
	{
		if (childContextType != "location")
			exceptionWithMsg(childContextType + "(child) is Invalid in " + parrentContextType + "(parrent) context");
	}
	else if (parrentContextType == "location")
	{
		if (childContextType != "location")
			exceptionWithMsg(childContextType + "(child) is Invalid in " + parrentContextType + "(parrent) context");
	}
}

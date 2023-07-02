#ifndef ALLDIRECTIVE_HPP
#define ALLDIRECTIVE_HPP

#include "DirAutoIndex.hpp"
#include "DirClientMaxBodySize.hpp"
#include "DirErrorPage.hpp"
#include "DirFastCgiParam.hpp"
#include "DirFastCgiPass.hpp"
#include "DirIndex.hpp"
#include "DirListen.hpp"
#include "DirRoot.hpp"
#include "DirServerName.hpp"
#include "DirReturn.hpp"

#include <iostream>

using namespace std;

class AllDirective{
	public:
		AllDirective();
		void print_all_key_value();
		AllDirective &operator =(AllDirective &directive);
		DirRoot root;
		DirAutoIndex autoindex;
		DirListen listen;
		DirServerName server_name;
		DirClientMaxBodySize client_max_body_size;
		DirErrorPage error_page;
		DirIndex index;
		DirFastCgiPass fastcgi_pass;
		DirFastCgiParam fastcgi_param;
		DirReturn return_d;
};


#endif
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include "MyNginx/NginxConfig.hpp"

std::string getFileContents(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file: " + filename);
    }

    std::ostringstream oss;
    oss << file.rdbuf();
    file.close();
    
    return oss.str();
}

int main() {
    string filename = "nginx.conf";
	string fileContents;
    try {
        fileContents = getFileContents(filename);
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    NginxConfig conf(fileContents);
	try
	{
        conf.config_server();
		conf.mainContext.print_raw_conf();
        conf.mainContext.print_conf();
        vector<pair<string, int> > vt = conf.find_all_port(); //-> listen하는 구조체
        for(int i = 0; i < vt.size(); i ++)
            cout << vt[i].first << " " << vt[i].second<< endl;
        // string address = "127.0.0.1";
        // string port = "81";
        // sReqMsg req;
        // req.host = "127.0.0.1";
        // req.requestTarget = "/aa";
        // req.contentLen = 0;
        // sResponseMsg res = conf.make_response(req, address, port);
        // cout << "code : " << res.code << endl;
        // cout << "location : " << res.location << endl;
        // cout << "body : " << res.body << endl;
	}
	catch(const ParseException &e)
	{
		cerr << e.what() << endl;
        return 1;
	}
    catch(const ContextException &e)
	{
		cerr << e.what() << endl;
        return 1;
	}
    catch(const DirectiveException &e)
	{
		cerr << e.what() << endl;
        return 1;
	}
    return 0;
}
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

    // NginxConfig conf(fileContents);
	try
	{
		NginxConfig conf(fileContents);
        conf.check_duplicate_server_name();
		// conf.mainContext.print_raw_conf();
        conf.set_default_server();
        // conf.mainContext.print_conf();
        vector<pair<string, int> > vt = conf.find_all_port(); //-> listen하는 구조체
        for(int i = 0; i < vt.size(); i ++)
            cout << vt[i].first << " " << vt[i].second<< endl;
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
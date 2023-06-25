#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include "NginxConfig.hpp"
#include "context_validate.cpp"
#include "directive_validate.cpp"

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

	try
	{
		NginxConfig conf(fileContents);
		conf.mainContext.print_conf();
        context_validate(conf.mainContext);
        directive_validate(conf.mainContext);
	}
	catch(const ParseException &e)
	{
		cerr << e.what() << endl;
        return 0;
	}
    catch(const ContextException &e)
	{
		cerr << e.what() << endl;
        return 0;
	}
    catch(const DirectiveException &e)
	{
		cerr << e.what() << endl;
        return 0;
	}
    return 0;
}
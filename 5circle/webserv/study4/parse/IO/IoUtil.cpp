#include "IoUtil.hpp"

int trans_error_code(int code)
{
	// "not found"
	if(code == 2)
	{
		return 404;
	}
	// fobidden
	if(code == 13)
	{
		return 403;
	}
	//별 의미없음
	return 405;
}

int getFileContents(const string& filename, string &buf) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
		cout << "not open\n";
		cout << errno << endl;
		cout << strerror(errno) << endl;
		return trans_error_code(errno);
    }

    std::ostringstream oss;
    oss << file.rdbuf();
    file.close();
    buf = oss.str();
    return 200;
}
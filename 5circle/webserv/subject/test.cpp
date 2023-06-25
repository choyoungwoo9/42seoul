#include <vector>
#include <string>
#include <iostream>

using namespace std;

vector<string> split(string str, string del)
{
	vector<string> ret;
	
	for(int i = str.find(del); i != string::npos; i=str.find(del))
	{
		ret.push_back(str.substr(0, i));
		str.erase(0, i+del.size());
	}
	ret.push_back(str);
	return ret;
}

int main()
{
	vector<string> ret = split("124:123", ":");
	for(int i = 0; i < ret.size(); i ++)
		cout << ret[i] << endl;
}
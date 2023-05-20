#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

std::map<std::pair<int, pair<int, int> >, int> db;

void print_err(string str)
{
	cout << "Error: " << str << endl;
}

void read_file(const std::string file_name)
{
	std::ifstream fstream(file_name);
	if(!fstream.is_open())
		throw exception();
	std::string str;
	getline(fstream, str);
	if(str != "date | value")
		print_err("format missmatch");
	while(getline(fstream, str))
	{
		
	}

	fstream.close();
}

void get_db()
{
	
}

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		cout << ("Error: could not open file.\n");
		return 1;
	}
	// get_db();
	read_file(argv[1]);
	
}
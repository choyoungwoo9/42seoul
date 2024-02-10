#ifndef DIRLISTEN_HPP
#define DIRLISTEN_HPP


#include "../Util/MyUtil.hpp"
#include "../Util/CustomException.hpp"
#include <string>
#include <map>
#include <vector>

using namespace std;

class DirListen{
	public:
		DirListen()
		{
			address = "0.0.0.0:8000";
			is_default_server = false;
		}

		DirListen &operator =(DirListen &param)
		{
			address = param.address;
			return *this;
		}

		void set_value(string &value)
		{
			string str = string_end_trim(value);
			if(str.empty())
			{
				cout << "listen empty\n";
				throw DirectiveException();
			}

			vector<string> parsed_white_space_str = white_space_split(str);
			if(parsed_white_space_str.size() > 2)
			{
				cout << "listen invalid_parameter\n";
				throw DirectiveException();
			}

			if(parsed_white_space_str.size() == 2)
			{
				if(parsed_white_space_str[1] != "default_server")
				{
					cout << "listen invalid_parameter\n";
					throw DirectiveException();
				}
				else
					is_default_server = true;
				str = parsed_white_space_str[0];
			}


			vector<string> vt = split(str, ":");
			// 65535
			for(int i = 0; i < vt.size(); i++)
			{
				if(vt[i].empty())
				{
					cout << vt[i] << endl;
					cout << "listen invalid value\n";
					throw DirectiveException();
				}
			}

			if(vt.size() == 1)
			{
				if(vt[0].find(".") != string::npos) //listen 127.0.0.1
				{
					vector<string> ipaddr = split(vt[0], "."); 
					if(ipaddr.size() != 4)
					{
						cout << "listen invalid value\n";
						throw DirectiveException();
					}
					for(int i = 0; i < ipaddr.size(); i++)
					{
						if(ipaddr[i].empty())
						{
							cout << "listen invalid value\n";
							throw DirectiveException();
						}
						for(int j = 0; j < ipaddr[i].size(); j++)
						{
							if(ipaddr[i][j] < '0' || ipaddr[i][j] > '9')
							{
								cout << "listen invalid value\n";
								throw DirectiveException();
							}
						}

						if(atoi(ipaddr[i].c_str()) < 0 || atoi(ipaddr[i].c_str()) > 255)
						{
							cout << "listen invalid value\n";
							throw DirectiveException();
						}
					}
					address = vt[0] + ":80";
				}
				else //listen 8000 case -> 0.0.0.0:8000
				{
					for(int i = 0; i < vt[0].size(); i++)
					{
						if(vt[0][i] < '0' || vt[0][i] > '9')
						{
							cout << "listen invalid value\n";
							throw DirectiveException();
						}
					}
					if(atoi(vt[0].c_str()) > 65535)
					{
						cout << "listen invalid value\n";
						throw DirectiveException();
					}
					address = "0.0.0.0:"+vt[0];
				}
			}
			else if(vt.size() == 2) //listen 127.0.0.1:8000 case
			{
				vector<string> ipaddr = split(vt[0], ".");
				if(ipaddr.size() != 4)
				{
					cout << "listen invalid value\n";
					throw DirectiveException();
				}
				for(int i = 0; i < ipaddr.size(); i++)
				{
					if(ipaddr[i].empty())
					{
						cout << "listen invalid value\n";
						throw DirectiveException();
					}
					for(int j = 0; j < ipaddr[i].size(); j++)
					{
						if(ipaddr[i][j] < '0' || ipaddr[i][j] > '9')
						{
							cout << "listen invalid value\n";
							throw DirectiveException();
						}
					}
					if(atoi(ipaddr[i].c_str()) < 0 || atoi(ipaddr[i].c_str()) > 255)
					{
						cout << "listen invalid value\n";
						throw DirectiveException();
					}
				}

				for(int i = 0; i < vt[1].size(); i++)
				{
					if(vt[1][i] < '0' || vt[1][i] > '9')
					{
						cout << "listen invalid value\n";
						throw DirectiveException();
					}
				}
				if(atoi(vt[1].c_str()) > 65535)
				{
					cout << "listen invalid value\n";
					throw DirectiveException();
				}
				address = str;
			}
			else
			{
				cout << "listen invalid value\n";
				throw DirectiveException();
			}
		}
		string address;
		bool is_default_server;
};

#endif
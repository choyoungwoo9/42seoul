#ifndef IOUTIL_HPP
#define IOUTIL_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

//finename으로 들어온 경로에 파일을 읽을수있으면 읽고, 200반환
//읽을수없으면 적절한 에러 반환
int getFileContents(const string& filename, string &buf);

#endif
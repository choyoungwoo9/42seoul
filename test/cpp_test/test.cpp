//sequence containers
//std::vector -> runtime에 크기 결정
//std::array -> comfile time에 크기 결정
//std::deque -> 여러개의 버퍼에 데이터를 나누어 저장함
//버퍼 1, 버퍼 2 이런식으로 버퍼공간이 있고
//버퍼1은 1, 2 버퍼2는 3, 4, 5 이런식으로 저장을 하고있음
//그러므로 6이라는 데이터를 추가하면 모두 새로할당 후 이동하는것이 아닌,
//버퍼공간을 하나만 추가하면 되므로 데이터의 맨 앞, 맨 뒤에 데이터를 삽입, 삭제
//가 필요할 경우 사용 
//std::list -> doubly 링크드리스트임
//std::forward_list -> singly linked list임

//Associative Containers
//데이터를 정렬된 상태로 유지하는 자료구조
//데이터 추가 삭제 접근의 시간복잡도 log n임
//그 댓가로 연산에 붙는 상수가 크고 사용하는 메모리 많음
//red black tree 기반임
//map은 키 , 값으로 저장함
//이때 키는 unique 해야함
//set의 경우 unique한 값으로 저장함
#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <map>
#include <set>
using namespace std;

int main()
{
	map<std::string, int> i;
	i["1"] = 3;
	i["2"] = 3;
	//i.insert("d", 3);
	cout << i["1"] <<endl;
	cout << i["2"] <<endl;
}
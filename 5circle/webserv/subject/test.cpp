#include <iostream>

using namespace std;

void func(int &num)
{
	num ++;
}

int main()
{
	int a = 3;
	int *ptr = &a;
	func(*ptr);
	cout << a << endl;
}
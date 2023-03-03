//
// Created by Youngwoo Cho on 3/2/23.
//
#include <iostream>
using namespace std;
class A{
public:
    A(){
        cout << "A const" << endl;
    }
    ~A(){
        cout << "A decon" << endl;
    }
};

void func(class A)
{

}

int main()
{
    A a;
    func(a);
}
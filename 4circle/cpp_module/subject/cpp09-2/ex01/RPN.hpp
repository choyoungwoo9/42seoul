#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <string>
#include <exception>

class RPN
{
public:
	RPN();
	RPN(const RPN &obj);
	RPN &operator=(const RPN &obj);
	~RPN();
	void processRPN(std::string input);
private:
	std::stack<int> RPNStack;
	
};

#endif
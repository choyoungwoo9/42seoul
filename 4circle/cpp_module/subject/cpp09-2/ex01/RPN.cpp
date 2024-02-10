#include "RPN.hpp"

RPN::RPN()
{
}

RPN::RPN(const RPN &obj)
{
	RPNStack = obj.RPNStack;
}

RPN &RPN::operator=(const RPN &obj)
{
	if (this == &obj)
		return *this;
	RPNStack = obj.RPNStack;
	return *this;
}

RPN::~RPN()
{
}

void RPN::processRPN(std::string input)
{
	std::stack<int> RPNStack;
	for(size_t i = 0; i < input.size(); i++)
	{
		if(input[i] == ' ')
			continue;
		if(input[i] >= '1' && input[i] <= '9')
		{
			RPNStack.push(input[i] - '0');
			continue;
		}

		if(RPNStack.size() < 2)
			throw std::exception();
		int num2 = RPNStack.top();
		RPNStack.pop();
		int num1 = RPNStack.top();
		RPNStack.pop();
		int num3;
		if(input[i] == '+')
			num3 = num1 + num2;
		else if(input[i] == '-')
			num3 = num1 - num2;
		else if(input[i] == '*')
			num3 = num1 * num2;
		else if(input[i] == '/' && num2 != 0)
			num3 = num1 / num2;
		else{
			throw std::exception();
		}
		RPNStack.push(num3);
	}
	if(RPNStack.size() != 1)
			throw std::exception();
	std::cout << RPNStack.top() << std::endl;
}

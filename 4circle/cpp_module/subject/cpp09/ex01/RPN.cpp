#include "RPN.hpp"

void operate(std::stack<int> &st, char oper)
{
	int num1 = st.top();
	st.pop();
	int num2 = st.top();
	st.pop();
	if(oper == '+')
		st.push(num2 + num1);
	else if(oper == '-')
		st.push(num2 - num1);
	else if(oper == '*')
		st.push(num2 * num1);
	else if(oper == '/')
	{
		if(num1 == 0)
			throw std::exception();
		st.push(num2 / num1);
	}
}

int is_num_next_valid(std::string &str, int index)
{
	if((unsigned long)index == str.size())
		return 1;
	if(str[index] == ' ' || str[index] == '\t')
		return 1;
	if(str[index] == '+' || str[index] == '-' || str[index] == '*' || str[index] == '/')
		return 1;
	return 0;
}

void RPN(std::string input)
{
	std::stack<int> st;
	for(int i = 0; (unsigned long)i < input.size(); i ++)
	{
		if(input[i] == ' ' || input[i] == '\t')
			continue;
		else if(input[i] == '+' && st.size() >= 2)
			operate(st, '+');
		else if(input[i] == '-' && st.size() >= 2)
			operate(st, '-');
		else if(input[i] == '*' && st.size() >= 2)
			operate(st, '*');
		else if(input[i] == '/' && st.size() >= 2)
			operate(st, '/');
		else if(input[i] >= '0' && input[i] <= '9' && is_num_next_valid(input, i+1))
			st.push(input[i]-'0');
		else
			throw std::exception();
	}
	if(st.size() != 1)
		throw std::exception();
	std::cout << st.top() << std::endl;
}
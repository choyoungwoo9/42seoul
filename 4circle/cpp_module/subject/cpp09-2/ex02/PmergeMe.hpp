#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <exception>
#include <string>
#include <cctype>
#include <cstdlib>
#include <algorithm>
#include <ctime>

struct numPair
{
	int n1;
	int n2;
} typedef numPair;

class PmergeMe
{
public:
	PmergeMe();
	PmergeMe(const PmergeMe &obj);
	PmergeMe &operator=(const PmergeMe &obj);
	~PmergeMe();
	void run(int arg, char **argv);

private:
	std::vector<int> originNumVector;
	std::vector<int> sortedNumVector;
	double vectorTime;
	void vectorProcess(int arg, char **argv);

	std::deque<int> originNumDeque;
	std::deque<int> sortedNumDeque;
	double dequeTime;
	void dequeProcess(int arg, char **argv);
};

#endif
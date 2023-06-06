#include "Span.hpp"

Span::Span(unsigned int N)
:storage_max(N), count(0)
{
	ar = new int[storage_max];
	if(!storage_max)
		ar = NULL;
}

Span::~Span()
{
	if(storage_max)
		delete[] ar;
}

Span::Span()
:storage_max(0), count(0), ar(NULL)
{
}

Span::Span(const Span &param)
:storage_max(param.storage_max), count(param.count)
{
	ar = new int[this->storage_max];
	if(!this->storage_max)
		ar = NULL;
	for(unsigned int i = 0; i < this->count; i ++)
		this->ar[i] = param.ar[i];
}

Span &Span::operator= (const Span &param)
{
	if(this->ar)
		delete[] this->ar;
	this->storage_max = param.storage_max;
	this->count = param.count;
	ar = new int[this->storage_max];
	if(!this->storage_max)
		ar = NULL;
	for(unsigned int i = 0; i < this->count; i ++)
		this->ar[i] = param.ar[i];
	return *this;
}

void Span::addNumber(int num)
{
	if(storage_max == count)
		throw std::exception();
	ar[count] = num;
	count ++;
}

unsigned int Span::shortestSpan()
{
	if(count == 0 || count == 1)
		throw std::exception();
	std::vector<int> v;
	for(unsigned int i = 0; i < count; i ++)
	{
		v.push_back(ar[i]);
	}
	sort(v.begin(), v.end());
	int m_diff = v[1]-v[0];
	for(unsigned int i = 1; i < count - 1; i ++)
	{
		if(v[i+1] - v[i] < m_diff)
			m_diff = v[i+1] - v[i];
	}
	return m_diff;
}
unsigned int Span::longestSpan()
{
	if(count == 0 || count == 1)
		throw std::exception();
	int m_min = ar[0];
	int m_max = ar[0];
	for(unsigned int i = 1; i < count; i ++)
	{
		if(ar[i] < m_min)
			m_min = ar[i];
		if(ar[i] > m_max)
			m_max = ar[i];
	}
	return m_max - m_min;
}
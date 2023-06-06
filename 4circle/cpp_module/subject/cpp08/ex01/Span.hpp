#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>

class Span
{
	public:
		Span(unsigned int N);
		Span(const Span &param);
		Span();
		~Span();
		Span &operator= (const Span &param);
		void addNumber(int num);
		unsigned int shortestSpan();
		unsigned int longestSpan();
		template<typename T>
		void addNumbers(T iter_s, T iter_e);
	
	private:
		unsigned int storage_max;
		unsigned int count;
		int *ar;
};

template<typename T>
void Span::addNumbers(T iter_s, T iter_e)
{
	for(; iter_s != iter_e; iter_s++)
	{
		addNumber(*iter_s);
	}
}

#endif
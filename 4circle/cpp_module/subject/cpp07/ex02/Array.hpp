#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <exception>

template <typename T>
class Array
{
	public:
		Array();
		~Array();
		Array(unsigned int n);
		Array(const Array<T> &param);
		Array<T> &operator= (Array<T> &param);
		T &operator[](unsigned int index) const;
		unsigned int size() const;
	private:
		T *ar;
		unsigned int ar_size;
};

template <typename T>
Array<T>::Array()
:ar(NULL), ar_size(0)
{
}

template <typename T>
Array<T>::~Array()
{
	if(ar)
	{
		delete[] ar;
		ar = NULL;
	}
}

template <typename T>
Array<T>::Array(unsigned int n)
:ar(new T[n]), ar_size(n)
{
	for(unsigned int i = 0; i < ar_size; i ++)
		ar[i] = 0;
}

template <typename T>
Array<T>::Array(const Array<T> &param)
:ar(new T[param.ar_size]), ar_size(param.ar_size)
{
	for(unsigned int i = 0; i < ar_size; i ++)
		ar[i] = param.ar[i];
}

template <typename T>
Array<T>& Array<T>::operator= (Array<T> &param)
{
	if(this != &param)
	{
		if(ar)
		{
			delete [] ar;
			ar = NULL;
		}
		ar_size = param.ar_size;
		ar = new T[ar_size];
		for(unsigned int i = 0; i < ar_size; i ++)
			ar[i] = param.ar[i];
	}
	return *this;
}

template <typename T>
T &Array<T>::operator[](unsigned int index) const
{
	if(index >= ar_size)
		throw std::exception();
	return ar[index];
}

template <typename T>
unsigned int Array<T>::size() const
{
	return ar_size;
}

#endif
#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <cstdlib>

typedef struct Data
{
	unsigned long long data;
}	Data;

class Serializer
{
	public:
		static uintptr_t serialize(Data *ptr);
		static Data* deserialize(uintptr_t raw);
	private:
		Serializer();
		~Serializer();
		Serializer(const Serializer &param);
		Serializer &operator =(const Serializer &param);
};

#endif
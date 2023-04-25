#ifndef SERIALIZE_HPP
#define SERIALIZE_HPP

#include <cstdlib>

typedef struct Data
{
	unsigned long long data;
}	Data;

uintptr_t serialize(Data *ptr);
Data* deserialize(uintptr_t raw);

#endif
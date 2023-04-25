#include "serialize.hpp"

#include <iostream>

int main()
{
	Data my_data;
	my_data.data = 23421231;
	uintptr_t ut = serialize(&my_data);
	Data* dt = deserialize(ut);

	std::cout << "ut : " << sizeof(ut) << ", " << ut << ", " << reinterpret_cast<Data *>(ut) << std::endl;
	std::cout << "ut : " << sizeof(dt) << ", " << dt << ", " << reinterpret_cast<uintptr_t>(dt) << std::endl;
}

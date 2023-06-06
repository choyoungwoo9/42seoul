#include "Serializer.hpp"

#include <iostream>

int main()
{
	Data my_data;
	my_data.data = 23421231;
	uintptr_t ut = Serializer::serialize(&my_data);
	Data* dt = Serializer::deserialize(ut);

	std::cout << "ut : " << sizeof(ut) << ", " << reinterpret_cast<Data *>(ut) << ", " << ut << std::endl;
	std::cout << "ut : " << sizeof(dt) << ", " << dt << ", " << reinterpret_cast<uintptr_t>(dt) << std::endl;
}

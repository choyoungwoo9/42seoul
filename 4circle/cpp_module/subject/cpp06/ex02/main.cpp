#include "Base.hpp"
#include "ft_util.hpp"

#include <unistd.h>

int main()
{
	Base *ins = generate();
	identify(ins);
	identify(*ins);
	delete ins;
}
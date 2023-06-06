#include "Base.hpp"
#include "FtUtil.hpp"

#include <unistd.h>

int main()
{
	for(int i = 0; i < 100; i ++)
	{
		Base *ins = generate();
		identify(ins);
		identify(*ins);
		delete ins;
	}
}
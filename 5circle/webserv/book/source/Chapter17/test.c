#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
char buf[100];
int main() {
	
    int flags = fcntl(0, F_GETFL, 0);
    flags |= O_NONBLOCK;
    fcntl(0, F_SETFL, flags);
   	printf("%zd\n", read(0, buf, 3)) ;

    return 0;
}

#include "parseContext.hpp"
#include "../nginxRunner.hpp"

int main()
{
	int fd = open("config", O_RDONLY);
	char buf[10000];
	int length = read(fd, buf, sizeof(buf));
	buf[length] = '\0';
	std::vector<std::string> tokens = tokenizer(buf);
	ParsedContext parsedMainContext = parse(tokens);

	// std::cout << "print Start!!!!!!!!!" << std::endl;
	// parseTreePrint(0, parsedMainContext);

	Context mainContext;
	parseTreeToContextTree(mainContext, parsedMainContext);
	// contextPrint(0, mainContext);

	NginxRunner webServer(mainContext);
	webServer.run();
}
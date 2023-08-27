#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // 필요한 환경 변수 설정
    putenv("QUERY_STRING=query=hello");
    putenv("REQUEST_METHOD=GET");
    putenv("CONTENT_TYPE=");
    putenv("CONTENT_LENGTH=");

    // PHP 실행
    FILE *fp = popen("/usr/bin/php -q /Users/youngwch/42/5circle/webserv/subject/solo2/php/hello.ph", "r");
    if (fp == NULL)
	{
        fprintf(stderr, "Failed to execute PHP script.\n");
        return 1;
    }

    // PHP 출력 결과 읽어오기
    char buffer[4096];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
        fwrite(buffer, 1, bytesRead, stdout);
    }

    // 파일 포인터 닫기
    pclose(fp);

    return 0;
}

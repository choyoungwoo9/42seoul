#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 1024

int main(void) {
    // 요청 메서드 확인
	// putenv("REQUEST_METHOD=GET");
	putenv("REQUEST_METHOD=POST");
	putenv("REQUEST_METHOD=10");
	putenv("QUERY_STRING=MY_QUERY");
    char *requestMethod = getenv("REQUEST_METHOD");
    if (requestMethod == NULL) {
        printf("Status: 500 Internal Server Error\n");
        printf("Content-type: text/plain\n\n");
        printf("Missing REQUEST_METHOD environment variable\n");
        return 1;
    }

    // GET 및 POST 매개변수 파싱
    char buffer[MAX_BUFFER_SIZE];
    if (strcmp(requestMethod, "GET") == 0) {
        char *queryString = getenv("QUERY_STRING");
        if (queryString != NULL) {
            strncpy(buffer, queryString, MAX_BUFFER_SIZE);
            buffer[MAX_BUFFER_SIZE - 1] = '\0';
        } else {
            buffer[0] = '\0';
        }
    } else if (strcmp(requestMethod, "POST") == 0) {
        char *contentLengthStr = getenv("CONTENT_LENGTH");
        if (contentLengthStr == NULL) {
            printf("Status: 400 Bad Request\n");
            printf("Content-type: text/plain\n\n");
            printf("Missing Content-Length header\n");
            return 1;
        }

        int contentLength = atoi(contentLengthStr);
        if (contentLength <= 0 || contentLength > MAX_BUFFER_SIZE) {
            printf("Status: 400 Bad Request\n");
            printf("Content-type: text/plain\n\n");
            printf("Invalid Content-Length\n");
            return 1;
        }

        fread(buffer, contentLength, 1, stdin);
        buffer[contentLength] = '\0';
    } else {
        printf("Status: 501 Not Implemented\n");
        printf("Content-type: text/plain\n\n");
        printf("Unsupported request method: %s\n", requestMethod);
        return 1;
    }

    // 환경 변수 설정
    printf("Content-type: text/html\n\n");
    printf("Status: 200 OK\n");

    // 표준 출력 처리
    printf("<html>\n");
    printf("<head><title>CGI Example</title></head>\n");
    printf("<body>\n");
    printf("<h1>CGI Example</h1>\n");
    printf("<p>Request Method: %s</p>\n", requestMethod);
    printf("<p>Query String: %s</p>\n", buffer);
    printf("</body>\n");
    printf("</html>\n");

    return 0;
}

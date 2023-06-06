#include <iostream>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    fd_set readfds;                   // 읽기 가능한 파일 디스크립터 집합
    FD_ZERO(&readfds);                // 파일 디스크립터 집합 초기화
    FD_SET(STDIN_FILENO, &readfds);   // 표준 입력(STDIN_FILENO)을 읽기 가능한 상태로 설정

    struct timeval timeout;
    timeout.tv_sec = 5;               // 타임아웃 시간을 5초로 설정
    timeout.tv_usec = 0;

    std::cout << "5초 동안 표준 입력을 확인합니다..." << std::endl;

    int result = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timeout);
    if (result == -1) {
        std::cerr << "select 함수 호출 중 오류 발생" << std::endl;
        return 1;
    } else if (result == 0) {
        std::cout << "타임아웃 발생!" << std::endl;
        return 0;
    }

    if (FD_ISSET(STDIN_FILENO, &readfds)) {
        std::cout << "표준 입력에 이벤트 발생!" << std::endl;
        // 표준 입력 처리 로직을 추가합니다.
    }

    return 0;
}

// select 함수는 주어진 파일 디스크립터들의 상태를 모니터링하고, 이벤트가 발생할 때까지 기다리는 함수입니다. 기본적인 사용법은 다음과 같습니다:

// fd_set 구조체를 초기화합니다.
// 관심 있는 파일 디스크립터를 fd_set에 추가합니다.
// select 함수를 호출하여 파일 디스크립터들의 상태를 모니터링합니다.
// select 함수는 이벤트가 발생하거나 타임아웃이 발생할 때까지 블로킹됩니다.
// select 함수가 반환되면, fd_set에 있는 파일 디스크립터 중 어떤 이벤트가 발생했는지 확인합니다.
#include <iostream>
#include <poll.h>

int main() {
    struct pollfd fds[1];
    fds[0].fd = STDIN_FILENO;  // 표준 입력(STDIN_FILENO)을 모니터링
    fds[0].events = POLLIN;    // 읽기 가능한 상태를 모니터링

    std::cout << "표준 입력을 확인합니다..." << std::endl;

    int result = poll(fds, 1, 5000);  // 5초 동안 모니터링
    if (result == -1) {
        std::cerr << "poll 함수 호출 중 오류 발생" << std::endl;
        return 1;
    } else if (result == 0) {
        std::cout << "타임아웃 발생!" << std::endl;
        return 0;
    }

    if (fds[0].revents & POLLIN) {
        std::cout << "표준 입력에 이벤트 발생!" << std::endl;
        // 표준 입력 처리 로직을 추가합니다.
    }

    return 0;
}
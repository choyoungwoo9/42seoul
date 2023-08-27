#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/event.h>

#define MAX_EVENTS 10

int main() {
    int kq = kqueue();
    if (kq == -1) {
        perror("kqueue");
        exit(1);
    }

    struct kevent events[MAX_EVENTS];
    struct timespec timeout = {0, 0};  // 블로킹하지 않기 위해 timeout을 0으로 설정

    int fd = 0;
    struct kevent event;
    EV_SET(&event, fd, EVFILT_READ, EV_ADD, 0, 0, NULL);

    if (kevent(kq, &event, 1, NULL, 0, NULL) == -1) {
        perror("kevent");
        exit(1);
    }

    while (1) {
		sleep(1);
        int num_events = kevent(kq, NULL, 0, events, MAX_EVENTS, &timeout);
        if (num_events == -1) {
            perror("kevent");
            exit(1);
        } else if (num_events > 0) {
            printf("%d events occurred\n", num_events);
            // 이벤트 처리 로직 구현
        } else {
            printf("No events occurred\n");
            // timeout 시간이 경과하였을 때 로직 구현
        }
    }

    close(kq);
    return 0;
}

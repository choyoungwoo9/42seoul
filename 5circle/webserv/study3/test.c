#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/event.h>
#include <ctype.h>

int main() {
    int kq;
    struct kevent change;
    struct kevent eventlist[10];  // 최대 10개의 이벤트를 저장할 배열
    char buffer[1024];

    // 파일 열기 (읽기 및 쓰기 모두 가능하도록)
    int fd = open("file", O_RDWR | O_NONBLOCK);
    if (fd == -1) {
        perror("파일 열기 실패");
        return 1;
    }

    // kqueue 생성
    kq = kqueue();
    if (kq == -1) {
        perror("kqueue 생성 실패");
        close(fd);
        return 1;
    }

    // 파일 디스크립터에 대한 읽기 이벤트 설정
    EV_SET(&change, fd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);

    // 이벤트를 kqueue에 등록
    if (kevent(kq, &change, 1, NULL, 0, NULL) == -1) {
        perror("이벤트 등록 실패");
        close(fd);
        close(kq);
        return 1;
    }

    while (1) {
        // 이벤트 대기
        int nev = kevent(kq, NULL, 0, eventlist, 10, NULL);
        if (nev == -1) {
            perror("이벤트 대기 실패");
            break;
        }

        for (int i = 0; i < nev; i++) {
            struct kevent event = eventlist[i];

            int current_fd = event.ident;  // 현재 이벤트와 연결된 파일 디스크립터

            if (event.flags & EV_EOF) {
                printf("파일의 끝에 도달하거나 오류 발생 (FD: %d)\n", current_fd);
                break;
            }

            if (event.filter == EVFILT_READ) {
                // 파일에서 데이터 읽기 (현재 이벤트와 연결된 파일 디스크립터 사용)
                ssize_t bytesRead = read(current_fd, buffer, sizeof(buffer));
                if (bytesRead == -1) {
                    perror("읽기 오류");
                    break;
                } else if (bytesRead == 0) {
                    printf("파일의 끝에 도달했습니다. (FD: %d)\n", current_fd);
                    break;
                } else {
                    printf("%zd 바이트의 데이터를 읽었습니다 (FD: %d): %s\n", bytesRead, current_fd, buffer);

                    // 데이터 수정 또는 처리 작업 수행
                    // 예: 데이터를 대문자로 변환
                    for (ssize_t j = 0; j < bytesRead; j++) {
                        buffer[j] = toupper(buffer[j]);
                    }

                    // 수정한 데이터를 다시 파일에 쓰기
                    ssize_t bytesWritten = write(current_fd, buffer, bytesRead);
                    if (bytesWritten == -1) {
                        perror("쓰기 오류");
                        break;
                    }
                    printf("%zd 바이트의 데이터를 수정하여 다시 썼습니다 (FD: %d)\n", bytesWritten, current_fd);
                }
            }
        }
    }

    // 리소스 정리
    close(fd);
    close(kq);

    return 0;
}

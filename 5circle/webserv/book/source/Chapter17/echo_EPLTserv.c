#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/event.h>

#define BUF_SIZE 4
#define KQUEUE_SIZE 50
void error_handling(char *buf);

int main(int argc, char *argv[])
{
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    socklen_t adr_sz;
    int str_len, i;
    char buf[BUF_SIZE];

    struct kevent kq_events[KQUEUE_SIZE];
    struct kevent kq_change;

    int kq, nevents;

    if (argc != 2) {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");
    if (listen(serv_sock, 5) == -1)
        error_handling("listen() error");

    kq = kqueue();
    if (kq == -1)
        error_handling("kqueue() error");

    EV_SET(&kq_change, serv_sock, EVFILT_READ, EV_ADD, 0, 0, NULL);
    if (kevent(kq, &kq_change, 1, NULL, 0, NULL) == -1)
        error_handling("kevent() error");

    while (1) {
        nevents = kevent(kq, NULL, 0, kq_events, KQUEUE_SIZE, NULL);
        if (nevents == -1) {
            puts("kevent() error");
            break;
        }

        puts("return kevent");
        for (i = 0; i < nevents; i++) {
            if (kq_events[i].ident == serv_sock) {
                adr_sz = sizeof(clnt_adr);
                clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &adr_sz);
                if (clnt_sock == -1)
                    error_handling("accept() error");

                EV_SET(&kq_change, clnt_sock, EVFILT_READ, EV_ADD, 0, 0, NULL);
                if (kevent(kq, &kq_change, 1, NULL, 0, NULL) == -1)
                    error_handling("kevent() error");

                printf("connected client: %d \n", clnt_sock);
            } else {
                clnt_sock = kq_events[i].ident;

                str_len = read(clnt_sock, buf, BUF_SIZE);
                if (str_len == 0) {    // close request!
                    EV_SET(&kq_change, clnt_sock, EVFILT_READ, EV_DELETE, 0, 0, NULL);
                    if (kevent(kq, &kq_change, 1, NULL, 0, NULL) == -1)
                        error_handling("kevent() error");

                    close(clnt_sock);
                    printf("closed client: %d \n", clnt_sock);
                } else {
                    write(clnt_sock, buf, str_len);    // echo!
                }
            }
        }
    }
    close(serv_sock);
    close(kq);
    return 0;
}

void error_handling(char *buf)
{
    fputs(buf, stderr);
    fputc('\n', stderr);
    exit(1);
}

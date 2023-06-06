#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/event.h>  // kqueue 헤더 파일

#define BUF_SIZE 4
#define MAX_EVENTS 50  // kqueue에서 처리할 이벤트의 최대 수

void set_nonblocking_mode(int fd);
void error_handling(const char *message);

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;
	socklen_t adr_sz;
	int str_len, i;
	char buf[BUF_SIZE];

	int kq, event_cnt;
	struct kevent *change_list;
	struct kevent *event_list;

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
	change_list = (struct kevent*)malloc(sizeof(struct kevent) * MAX_EVENTS);
	event_list = (struct kevent*)malloc(sizeof(struct kevent) * MAX_EVENTS);

	EV_SET(&change_list[0], serv_sock, EVFILT_READ, EV_ADD, 0, 0, NULL);  // 서버 소켓을 등록

	while (1) {
		event_cnt = kevent(kq, change_list, 1, event_list, MAX_EVENTS, NULL);
		if (event_cnt == -1) {
			puts("kevent() error");
			break;
		}

		puts("return kevent");
		for (i = 0; i < event_cnt; ++i) {
			if (event_list[i].ident == serv_sock) {
				adr_sz = sizeof(clnt_adr);
				clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &adr_sz);
				set_nonblocking_mode(clnt_sock);
				EV_SET(&change_list[0], clnt_sock, EVFILT_READ, EV_ADD, 0, 0, NULL);  // 클라이언트 소켓을 등록
				kevent(kq, change_list, 1, NULL, 0, NULL);  // 등록된 이벤트를 kqueue에 반영
				printf("connected client: %d \n", clnt_sock);
			}
			else {
				while (1) {
					str_len = read(event_list[i].ident, buf, BUF_SIZE);
					if (str_len == 0) {  // close request!
						EV_SET(&change_list[0], event_list[i].ident, EVFILT_READ, EV_DELETE, 0, 0, NULL);  // 클라이언트 소켓을 삭제
						kevent(kq, change_list, 1, NULL, 0, NULL);  // 등록된 이벤트를 kqueue에 반영
						close(event_list[i].ident);
						printf("closed client: %lu \n", event_list[i].ident);
						break;
					}
					else if (str_len < 0) {
						if (errno == EAGAIN)
							break;
					}
					else {
						write(event_list[i].ident, buf, str_len);  // echo!
					}
				}
			}
		}
	}

	close(serv_sock);
	close(kq);
	free(change_list);
	free(event_list);
	return 0;
}

void set_nonblocking_mode(int fd)
{
	int flag = fcntl(fd, F_GETFL, 0);
	fcntl(fd, F_SETFL, flag | O_NONBLOCK);
}

void error_handling(const char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/select.h>

#define BUF_SIZE 100

int main(int argc, char *argv[])
{
	// 서버 소켓, 클라이언트 소켓
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_addr, clnt_addr;
	struct timeval timeout;
	fd_set reads, cpy_reads;
	int fd_max, fd_num;
	socklen_t addr_size;
	int i, str_len;

	char buf[BUF_SIZE];

	if (argc != 2)
	{
		printf("Usage : ./program_name <port>\n");
		exit(1);
	}

	// socket
	serv_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serv_sock == -1)
	{
		perror("error : failed socket()");
		return 0;
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[1]));

	if(bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1){
		perror("error : failed bind()");
		return 0;
	}

	if (listen(serv_sock, 1) == -1){
		perror("error : failed listen");
		return 0;
	}

	FD_ZERO(& reads);
	FD_SET(serv_sock, & reads);
	fd_max = serv_sock;

	while(1){
		//이전 상태 저장
		cpy_reads = reads;
		timeout.tv_sec = 5;
		timeout.tv_usec = 50000;

		if((fd_num = select(fd_max + 1, &cpy_reads, 0, 0, &timeout)) == -1){
			printf("fd_num : %d\n", fd_num);
			perror("select() error");
			break;
		}

		//bit가 1인 필드 없음
		if(fd_num == 0)
			continue;
		
		// 발견되면 fd 순회함
		for(int i = 0; i < fd_max+1; i++){
			if(FD_ISSET(i, &cpy_reads)){
				if(i == serv_sock){
					printf("putin serv_sock\n");
					addr_size = sizeof(clnt_addr);

					clnt_sock = accept(serv_sock, (struct sockaddr *) &clnt_addr, &addr_size);
					FD_SET(clnt_sock, &reads);
					if(fd_max < clnt_sock)
						fd_max = clnt_sock;
					printf("connected client : %d \n", clnt_sock);
				}
				else{
					str_len = read(i, buf, BUF_SIZE);
					if(str_len <= 0){
						FD_CLR(i, &reads);
						close(i);
						printf("close client : %d \n", i);
					}
					else{
						write(i, buf, str_len);
					}
				}
			}
		}
	}
	close(serv_sock);
	return 0;
}

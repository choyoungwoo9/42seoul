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

int main(int argc, char * argv[]) {
  int serv_sock, clnt_sock; // fd : file descriptor
  struct sockaddr_in serv_addr, clnt_addr;
  struct timeval timeout;
  fd_set reads, cpy_reads;
  int fd_max, fd_num;
  socklen_t addr_size;
  int i, str_len;

  char buf[BUF_SIZE];

  if (argc != 2) {
    printf("Usage : ./program_name <port>\n");
    exit(1);
  }

  // socket
  serv_sock = socket(PF_INET, SOCK_STREAM, 0);
  if (serv_sock == -1) {
    perror("error : failed socket()");
  }

  memset( & serv_addr, 0, sizeof(serv_addr)); // 메모리 초기화
  serv_addr.sin_family = AF_INET; // 주소 체계 저장
  serv_addr.sin_port = htons(atoi(argv[1])); // 인자로 받은 port 번호

  // sockaddr* : sockaddr_in / sockaddr_un 이든 형변환
  if (bind(serv_sock, (struct sockaddr * ) & serv_addr, sizeof(serv_addr)) == -1) { // 소켓에 주소 할당
    perror("error : failed bind()");
    return 0;
  }

  if (listen(serv_sock, 5) == -1) { // 클라이언트 연결 대기 & 요청 queue에 저장
    perror("error : failed listen()");
    return 0;
  }

  // select I/O
  FD_ZERO( & reads); // 0으로 초기화
  FD_SET(serv_sock, & reads); // fd에 해당하는 bit 세팅
  fd_max = serv_sock;


  while (1)
  {
    // 이전 상태 저장
    cpy_reads = reads;
    timeout.tv_sec = 5;
    timeout.tv_usec = 50000;

    // select(nfds, readfds, write, err, timeout)
    if ((fd_num = select(fd_max + 1, & cpy_reads, 0, 0, & timeout)) == -1) {
      printf("fd_num : %d\n", fd_num);
      perror("select() error");
      break;
    }

    // bit 값이 1인 필드 없음 = 발견된 read data 없음
    if (fd_num == 0)
      continue;

    // 발견되면 fd 다 훑음 = O(n)
    for (i = 0; i < fd_max + 1; i++) {
      if (FD_ISSET(i, & cpy_reads)) {
        if (i == serv_sock) { // data 발생한 fd 찾으면
          printf("putin serv_sock\n");
          addr_size = sizeof(clnt_addr);

          // queue에서 연결 요청 하나씩 꺼내서 해당 client와 server socket 연결
          clnt_sock = accept(serv_sock, (struct sockaddr * ) & clnt_addr, & addr_size);
          FD_SET(clnt_sock, & reads);
          if (fd_max < clnt_sock)
            // loop 돌아야 하므로 fd 큰쪽으로 맞춤
            fd_max = clnt_sock;
          printf("connected client : %d \n", clnt_sock);
        } 
          else {
          str_len = read(i, buf, BUF_SIZE); // 데이터 수신
          if (str_len <= 0) {
            FD_CLR(i, & reads);
            close(i);
            printf("close client : %d \n", i);
          } 
            else {
            // client로echo 응답
            write(i, buf, str_len);
          }
        }
      }
    }
  }
  close(serv_sock);
  return 0;
}
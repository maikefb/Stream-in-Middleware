#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <pthread.h>

#define MSGLEN_MAX 50
#define PORT 43210

void *client_master(void*)
{
  int s0, status = 0;
  char buf[32];
  struct sockaddr_in cli_sock;
  socklen_t len = sizeof(cli_sock);

  // Conexao UDP
  s0 = socket(AF_INET, SOCK_DGRAM, 0);
  if (s0 < 0) {
    printf("(%d) Erro no socket\n", s0);
  }
  bzero(&cli_sock, sizeof(cli_sock));
  cli_sock.sin_addr.s_addr = htonl(INADDR_ANY);
  cli_sock.sin_port = htons(PORT) ;
  cli_sock.sin_family = AF_INET;

  if (bind(s0, (sockaddr *)&cli_sock, len) < 0) {
    printf("Erro no bind\n");
  }

  recvfrom(s0, buf, sizeof(buf), 0, (sockaddr *)&cli_sock, &len);
  printf("[BUFFER]: %s\n", buf);

  close(s0);
  pthread_exit(0);
}

int main()
{
  int sock, s0, status, buflen = MSGLEN_MAX;
  unsigned sinlen;
  char buffer[MSGLEN_MAX];
  struct sockaddr_in sock_in, s0_in, s0_client;
  int yes = 1;
  sinlen = sizeof(struct sockaddr_in);


  pthread_t cli_master;
  pthread_create(&cli_master, NULL, client_master, NULL);
  pthread_join(cli_master, NULL);
/*
// TCP/IP
  s0 = socket (AF_INET, SOCK_STREAM, 0);

  memset(&s0_in, 0, sinlen);
  s0_in.sin_addr.s_addr = inet_addr("192.168.25.3");
  s0_in.sin_port = htons(PORT);
  s0_in.sin_family = AF_INET;

  status = bind(s0, (struct sockaddr *)&s0_in, sinlen);
  printf("[Status]>> %d ", status);
  status = connect(s0, (struct sockaddr *)&s0_client, (socklen_t)sinlen);
  printf("[Status]>> %d ", status);

  while(1) {
    printf("[MSG]>> ");
    scanf("%s", buffer);
    send(s0, buffer, buflen, 0);
    recv(s0, buffer, buflen, 0);
    printf("[RECV] %s", buffer);
  }
  close(s0);
*/
}

#include <stdio.h>
#include <stdlib.h>
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


int pegaip(char *var)
{
 FILE *fd;
 char ip[16];
 system("caminho=`pwd`\"/ip.txt\"; hostname -I | cut -d ' ' -f 1 > $caminho");
 fd = fopen("ip.txt", "r");
 if (!fd) {
  return 1;
 }
 fscanf(fd, "%s", ip);
 strcpy(var, ip);
 system("rm ip.txt");
 fclose(fd);
 return 0;
}


int scan_clients()
{
  int sock, status, buflen = 32, sinlen, yes = 1;
  char buf[32], my_ip[16];
  struct sockaddr_in sock_in;
  sinlen = sizeof(struct sockaddr_in);

  sock = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  bzero(&sock_in, sinlen);
  sock_in.sin_addr.s_addr = htonl(-1);
  sock_in.sin_port = htons(PORT);
  sock_in.sin_family = AF_INET;

  //if (bind(sock, (struct sockaddr *)&sock_in, sinlen) < 0) {
  //  printf("Erro no bind do scan_clients\n");
  //  return -1;
  //}
  status = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(int));
  pegaip(my_ip);
  strcpy(buf, my_ip);
  status = sendto(sock, buf, sizeof(buf), 0, (struct sockaddr *)&sock_in, sinlen);
  printf("sendto Status = %d\n", status);

  close(sock);
  return 0;
}

void *server_master(void*)
{
  char meu_ip[16];

  pegaip(meu_ip);
  printf("[SERVIDOR] Meu IP: <%s>\n", meu_ip);
   if (scan_clients() < 0) {
     printf("ERRO no scan_clients\n");
   }

  pthread_exit(0);
}

int main()
{
  int s0, status, buflen = MSGLEN_MAX;
  unsigned sinlen;
  char buffer[MSGLEN_MAX];
  struct sockaddr_in s0_in, s0_client;
  sinlen = sizeof(struct sockaddr_in);

  pthread_t serv_master;
  pthread_create(&serv_master, NULL, server_master, NULL);
  pthread_join(serv_master, NULL);
/*
// TCP/IP
  s0 = socket (AF_INET, SOCK_STREAM, 0);

  memset(&s0_in, 0, sinlen);
  s0_in.sin_addr.s_addr = INADDR_ANY;
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

// Bibliotecas do C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
// Bibliotecas do C++
#include <iostream>
#include <ctime>
// Bibliotecas do C para thread
#include<pthread.h>
// Bibliotecas do C para semaforos
#include<semaphore.h>
// Bibliotecas do C++ para opencv
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
// Bibliotecas do C para socket
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

//Define de habilitação da camêra USB, caso utilize a Câmera da Raspberry, comentar esta linha.
//#define ENABLE_USBCAM

//Define de habilitação da RaspiCam, caso não possua a camêra ou as bibliotecas comentar esta linha.
#define ENABLE_RASPICAM

//Include e chamada do ambiente da RaspiCam.
#ifdef ENABLE_RASPICAM
  #include <raspicam/raspicam_cv.h> 
  using namespace raspicam;
#endif

//PORT_MASTER porta utilizada pela thread_master, PORT porta utilizada pelas threads_filhas  
#define PORT_MASTER 3128
#define PORT 3129

//Variavel para contar os pacotes perdidos
#define N 40000

#define LARGURA 640
#define ALTURA 480


// g++ usercall.cpp -pthread -o midd `pkg-config --cflags --libs opencv`

using namespace std;
using namespace cv;

/*  Estrutura que contem os
  paramtros passsados para as
      funcoes do sistema */

typedef struct {
  int callnumber;
  unsigned char *p0;
  unsigned char *p1;
  unsigned char *p2;
  unsigned char *p3;
}parameters;

/* caso contenha 1 indica que o
 * recurso esta ativo e caso 0 desativo
 */
typedef struct  {
  int stream;
  int video;
  int photo;
}control_t;

typedef struct {
    int num_pack;
    int tam_buff[1];
}packet;

enum callnumber_t{
  SERVER_MASTER_INIT,
  CLIENT_MASTER_INIT,
  STREAM_START,
  STREAM_STOP,
  STREAM_QT,
  PHOTO_IMED,
  PHOTO_PERIOD_START,
  PHOTO_PERIOD_STOP,
  VIDEO_START,
  VIDEO_STOP
};

enum error{
	ERROR,
	ERROR_SOCKET,
	ERROR_BIND,
	ERROR_LISTEN,
	ERROR_ACCEPT,
	ERROR_CONNECT,
	ERRO_TST_CLIMS,
	ERRO_TST_CLIMB,
	ERRO_TST_CLIS,
	ERRO_TST_CLIB,
	ERRO_TST_SERVMS,
	ERRO_TST_SERVMB,
	ERRO_TST_SERVS,
	ERRO_TST_SERVB
};

enum stt{
  OFF,
  ON
};

extern pthread_t serv_master;
extern pthread_t cli_master;

/* invoke - muda de contexto (usuario/sistema)
 * parameters: contem parametros usados pela funcao chamada
 *
 * return   repassa retorno da funcao do sistema
 */
int invoke(parameters *arg);
/* server_master - inicia sistema de servidores
 * parameters: contem parametros usados pela funcao chamada
 *
 * return   0
 */
void *server_master(void *arg);
void *server(void *arg);
/* client_master - inicia sistema de clientes
 * parameters: contem parametros usados pela funcao chamada
 *
 * return   0
 */
void *client_master(void *arg);
void *client(void *arg);
/* pegaip() - Esta função salva o ip da maquina em uma string 16(str[16])
 *
 * var : Variavel que recebera o endereço de onde esta salvo o ip
 * 	  a string deve ter tamanho minimo 16
 *
 * return: Retorna 1 se nao conseguir pega o ip e 0 se conseguir
 */
int pegaip(char *var);
/* scan_clients - mapeia os clientes conectados na rede
 *
 * return   0
 */
int scan_clients();
/* stream - mostra stream da camera
 *
 * return 0
 */
void *stream(void *arg);
Mat stream_qt();

void *video(void *arg);

void *photo_periodical(void *arg);
void photo();
void debuger(int erro);
void conta_pacotes(int pkt);
/* funcao principal (usada para teste) */
//int main(int argc, char const *argv[]);

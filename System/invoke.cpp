#include "invoke.hpp"

// g++ invoke.cpp -pthread -o midd `pkg-config --cflags --libs opencv`

// thread que controlam o fluxo do programa cliente e sevidor
pthread_t serv_master;
pthread_t cli_master;
int delay = 0,s0,sock,s1,s2;
// variavel de controle de estado (on/off) dos recursos (stream, video, photo)
control_t control;
// semaforo entre o recebimento e o stream da imagem
sem_t sem_stream, sem_video, sem_foto, sem_fotoP, sem_frame, sem_streamQT;

// matriz da imagem (usar semaphoros pra acessa-la!)
Mat frame = Mat::zeros(ALTURA, LARGURA, CV_8UC3);
Mat frame_photo = Mat::zeros(ALTURA, LARGURA, CV_8UC3);


Mat f[10];

struct sockaddr_in cli_sock,cli;
  socklen_t sock_len;
  struct sockaddr_in sock_in,serv;

int invoke(parameters *arg)
{
 int r = 0;
 pthread_t t1, t2, t3;
  switch (arg->callnumber) {
  case SERVER_MASTER_INIT:
    pthread_create(&serv_master, NULL, server_master, (void *) arg);
    break;
  case CLIENT_MASTER_INIT:
    pthread_create(&cli_master, NULL, client_master, (void *) arg);
    break;
  case STREAM_START:
    control.stream = ON;
    //pthread_create(&t1, NULL, stream, (void *) arg);
    break;
  case STREAM_STOP:
    control.stream = OFF;
    break;
  case STREAM_QT:
    stream_qt();
    break;
  case PHOTO_IMED:
    photo();
    break;
  case PHOTO_PERIOD_START:
    char str[32];
    delay = (long)*(arg->p0);
    control.photo = ON;
    //pthread_create(&t2, NULL, photo_periodical, (void *) arg);
    break;
  case PHOTO_PERIOD_STOP:
    control.photo = OFF;
    break;
  case VIDEO_START:
    control.video = ON;
    //pthread_create(&t3, NULL, video, (void *) arg);//tirar esta linha, colocar ela em outro lugar
    break;
  case VIDEO_STOP:
    control.video = OFF;
    break;
  default:
    break;
  }
  return r; // restaura contexto
}

void *client_master(void *arg)
{
  parameters *par = (parameters *)arg;
  int status = 0;
  char buf[32];
  pthread_t cli;

  socklen_t len = sizeof(cli_sock);

  // Conexao UDP
  s0 = socket(AF_INET, SOCK_DGRAM, 0);
  if (s0 < 0) {
    debuger(ERRO_TST_CLIMS);
  }

  bzero(&cli_sock, sizeof(cli_sock));
  cli_sock.sin_addr.s_addr = htonl(INADDR_ANY);
  cli_sock.sin_port = htons(PORT_MASTER) ;
  cli_sock.sin_family = AF_INET;

  if (bind(s0, (sockaddr *)&cli_sock, len) < 0) {
    debuger(ERRO_TST_CLIMB);
  }

  // Espera sinal do servidor
  while(1) {
    while(1) {
      recvfrom(s0, buf, sizeof(buf), 0, (sockaddr *)&cli_sock, &len);
      if (buf[0] == 'S') {
        printf("[CLIENTE]: Achei um servidor (%s)\n", (buf + 1));
        break;
      }
    }
    par->p0 = (unsigned char *)(buf+1); // IP do servidor
    close(s0);
    pthread_create(&cli, NULL, client,(void *) par);
    pthread_join(cli, NULL);
  }

  pthread_exit(0);
}

void *client(void *arg)
{
  //Criando um Arquivo TXT para salvar os dados



  parameters *par = (parameters *)arg;
  int bytes,r[1];
  int contapacotes = 0; //contar numero de pacotes envIADOS
  char buf[32];
  Mat frame = Mat::zeros(ALTURA, LARGURA, CV_8UC3);
  int imgSize = frame.total() * frame.elemSize();

  uchar *frm = frame.data;
  int sinlen = sizeof(struct sockaddr_in);
  socklen_t slen = sizeof(cli);

  s1 = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  if (s1 < 0) {
    debuger(ERRO_TST_CLIS);
  }

  memset(&cli, 0 ,slen);
  bzero(&(cli), sizeof(cli));
  cli.sin_addr.s_addr = inet_addr((char *)par->p0);
  cli.sin_port = htons(PORT);
  cli.sin_family = AF_INET;
  int yes = 1;
  int tamFrame = frame.total()*frame.elemSize();
  int status = setsockopt(s1, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(int));

  sleep(5);

	clock_t t_start;
	clock_t t_end;

  #ifdef ENABLE_RASPICAM
    RaspiCam_Cv CAM;
    CAM.set(CV_CAP_PROP_FORMAT, CV_8UC3);
    CAM.set(CV_CAP_PROP_FRAME_HEIGHT,480);
    CAM.set(CV_CAP_PROP_FRAME_WIDTH,640);
    if(!CAM.open()){
      printf("ERRO NA CÂMERA");
    }
  #endif  

  #ifdef ENABLE_USBCAM 
    VideoCapture cam(1);
  #endif  

  int ax = 1;
  
  //VARIAVEIS DO TESTE DE BUFFER
  vector <uchar> encode;
  Mat sendTST;
  //VARIAVEIS DO TESTE DE BUFFER
	
 while(1) {
 //while (contapacotes< N ) {
    #ifdef ENABLE_RASPICAM
      CAM.grab();
      CAM.retrieve(frame);
    #endif

    #ifdef ENABLE_USBCAM  
      cam.read(frame);
    #endif
      
    resize(frame,sendTST,Size(300,300),0,0, INTER_LINEAR);
    //cvtColor(frame,frame,CV_BGR2RGB);
    //sendTST = frame;
    vector<int> foto_parametros;
    foto_parametros.push_back(CV_IMWRITE_JPEG_QUALITY);
    foto_parametros.push_back(80);
    imencode(".jpg",sendTST,encode,foto_parametros);
    int total = 1 + (encode.size() - 1) / 4096;
    int ibuff[1];
    ibuff[0] = total;
    bytes = sendto(s1,ibuff,sizeof(int),0,(struct sockaddr *)&cli, slen);
    //contapacotes ++; //CONTADOR PACOTES ENVIADOS
    //printf("Pacote enviado enviado: %d\n",contapacotes);

    for (int i = 0; i < total; i++) {
    	bytes = sendto(s1,&encode[i*4096],4096,0,(struct sockaddr *)&cli, slen);
      	//contapacotes ++; //CONTADOR PACOTES ENVIADOS
        printf("BYTES ENVIADOS NA SEGUNDA MENSAGEM --> %d\n",bytes);
        //printf("Pacote enviado enviado: %d\n",contapacotes);   
    }

  }
  /* -------Fim-aplicacao------- */
  close(s0);
  pthread_exit(0);
}

void *server_master(void *arg)
{
  parameters *par = (parameters *)arg;
  char meu_ip[16];
  pthread_t serv;
  pthread_t t1, t2, t3;    
    
  pegaip(meu_ip);
  //printf("[SERVIDOR] Meu IP: <%s>\n", meu_ip);
   if (scan_clients() < 0) {
     printf("ERRO no scan_clients\n");
   }

  pegaip(meu_ip);
  par->p0 = (unsigned char *)(meu_ip);
  sem_init(&sem_stream, 0, 0); //Mudei aqui de 1 para 0
  sem_init(&sem_foto, 0, 0); //Mudei aqui de 1 para 0
  sem_init(&sem_video, 0, 0);//Acrescentei esta linha
  sem_init(&sem_fotoP, 0, 1);
  sem_init(&sem_frame, 0, 1);
  sem_init(&sem_streamQT, 0, 0);

  pthread_create(&serv, NULL, server,(void *) par);
  pthread_create(&t1, NULL, stream, (void *) arg);
  pthread_create(&t3, NULL, video, (void *) arg);
  pthread_create(&t2, NULL, photo_periodical, (void *) arg);

  pthread_join(serv, NULL);
  pthread_exit(0);
}

void *server(void *arg)
{
  int sock_fd, s0, length, bytes = 0;
  char buf[32];
  parameters *par = (parameters *)arg;
  socklen_t sock_len;
  int imgSize = frame.total() * frame.elemSize();
  uchar *frm = frame.data;
  vector<int> foto_parametros;
  foto_parametros.push_back(CV_IMWRITE_JPEG_QUALITY);
  foto_parametros.push_back(95);

  socklen_t slen = sizeof(serv);
  s2 = socket(AF_INET, SOCK_DGRAM, 0);

  if (s2 < 0) {
    debuger(ERRO_TST_SERVS);
  }

  bzero(&serv, sizeof(serv));
  serv.sin_addr.s_addr = htonl(INADDR_ANY);
  serv.sin_port = htons(PORT) ;
  serv.sin_family = AF_INET;

  int retVal = bind(s2, (sockaddr *)&serv, sizeof(serv));
  
  if (retVal < 0) {
    debuger(ERRO_TST_SERVB);
  }
  
  length = sizeof(serv);

  // Inicia a fila ? Modificar aqui para gerar uma thread que fica olhando pra fila ?

  int i;

  for (i = 0; i < 10; i++) {
    f[i] = Mat::zeros(ALTURA, LARGURA, CV_8UC3);
  }

  // Incia a fila ? Modificar aqui para gerar uma thread que fica olhando pra fila ?

  // Recebe imagem do cliente

  int ay = 0;
  int tamFrame = frame.total()*frame.elemSize();
  Mat frameTST = Mat::zeros(ALTURA, LARGURA, CV_8UC3);

  //VARIAVEIS DO TESTE DE BUFFER
  int recvMSG;
  char iBUFF[65540];
  int ibuff;
  int contapacotes = 0 ; 
  //VARIAVEIS DO TESTE DE BUFFER
    
  while (contapacotes < N) {
    do {
    	recvMSG = recvfrom(s2,&iBUFF,65540,0,(sockaddr *)&serv, &slen);
    	contapacotes ++ ;
    	conta_pacotes(contapacotes);
    } while(recvMSG > sizeof(int));

    int total_pack = ((int *) iBUFF)[0];
    char *longbuf = new char[4096*total_pack];

    for (int i = 0; i < total_pack; i++) {
        recvMSG = recvfrom(s2,&iBUFF,65540,0,(sockaddr *)&serv, &slen);
        contapacotes ++ ;
        conta_pacotes(contapacotes);
        if (recvMSG != 4096) {
		    continue;
	    }
	    memcpy(&longbuf[i*4096],iBUFF,4096);
        
    }

    Mat rawData = Mat(1,4096*total_pack, CV_8UC3, longbuf);
    Mat frameMod = imdecode(rawData, CV_LOAD_IMAGE_COLOR);
    frame = frameMod;
    frame_photo = frame;
    free(longbuf);
    sem_post(&sem_stream);
  	sem_post(&sem_streamQT);
    sem_post(&sem_video);
    sem_post(&sem_fotoP);
    
  }
  close(sock_fd);
  pthread_exit(0);
}

int scan_clients()
{
  int status, buflen = 32, sinlen, yes = 1;
  char buf[32], my_ip[16];

  sinlen = sizeof(sock_in);

  sock = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  bzero(&sock_in, sinlen);
  sock_in.sin_addr.s_addr = htonl(-1);
  sock_in.sin_port = htons(PORT_MASTER);
  sock_in.sin_family = AF_INET;

  status = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(int));
  // Envia IP do servidor
  pegaip(my_ip);
  sprintf(buf,"S%s",my_ip);
  sendto(sock, buf, sizeof(buf), 0, (struct sockaddr *)&sock_in, sinlen);

  close(sock);
  return 0;
}

void *stream(void *arg)
{
  if (control.stream == ON) {	  	
	char window[] = {"-===<| CAM |>===-"};
	namedWindow(window, WINDOW_NORMAL);
	while(1){
		sem_wait(&sem_stream);
		if(control.stream == ON) {
			imshow(window, frame);
			waitKey(20);
		}
		sem_post(&sem_frame);
	}
	destroyAllWindows();
    //video.release();
    pthread_exit(0);
  }	  
}

Mat stream_qt()
{
  sem_wait(&sem_streamQT);
  Mat frame_qt = frame;
  cvtColor(frame_qt,frame_qt,CV_BGR2RGB);  
  //sem_post(&sem_frame);
  return frame_qt;
}

void *photo_periodical(void *arg)
{
  parameters *par = (parameters *)arg;
  int i;
  while(1) {
  	sem_wait(&sem_fotoP);
  	if(control.photo == ON) {
    		photo();
		//sem_post(&sem_frame);
	  	sleep((int)delay);
  	}//else {
	//	sem_post(&sem_frame);
	//}    
  }
  pthread_exit(0);
}

void photo()
{
  time_t t;
  char foto[32];
  struct tm *tempo;
  vector<int> foto_parametros;
  foto_parametros.push_back(CV_IMWRITE_JPEG_QUALITY);
  foto_parametros.push_back(95);

  time(&t);
  tempo = gmtime(&t);

  sprintf(foto,"FOTO-%d-%d-%d-%d:%d:%d.jpg", tempo->tm_year + 1900, tempo->tm_mon, tempo->tm_mday, tempo->tm_hour, tempo->tm_min, tempo->tm_sec);

  //sem_wait(&sem_foto);
  cvtColor(frame_photo,frame_photo,CV_BGR2RGB);
  imwrite(foto, frame_photo, foto_parametros);    
  //sem_post(&sem_foto);//comentei esta linha

  return;
}

void *video(void *arg)
{
	if (control.video == ON) {
		const String vi("Avideo.avi");
		Size tamanho(640,480);
		VideoWriter video(vi, CV_FOURCC('M','J','P','G'), 3.0, tamanho, true);

		while (control.video == ON) {
			sem_wait(&sem_video);
			video.write(frame);    
		}
		video.release();
  }
  //pthread_exit(0);
}

void debuger(int erro)
{
  FILE *fd;
  time_t t;
  char msg[32];
  struct tm *tempo;

  time(&t);
  tempo = gmtime(&t);
  sprintf(msg,"%d-%d-%d-%d:%d:%d - ERRO Nº%d", tempo->tm_year + 1900, tempo->tm_mon, tempo->tm_mday, tempo->tm_hour, tempo->tm_min, tempo->tm_sec, erro);

  fd = fopen("Debug.txt", "a+");
  fprintf(fd, "%s\n", msg);
  fclose(fd);
}

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

void conta_pacotes(int pkt){

  ofstream file;
  file.open("Dados Pacotes.txt");
  file << "Pacote : " << pkt << endl;
  file.close();
  
}

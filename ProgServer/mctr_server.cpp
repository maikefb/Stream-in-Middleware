#include "../System/usercall.hpp"

// g++ invoke.cpp main.cpp -pthread -o midd `pkg-config --cflags --libs opencv`

typedef struct {
	unsigned stream;
	unsigned video;
	unsigned fperiod;
} status;

int main(int argc, char const *argv[]) {
  //parameters par;
  //pthread_t t1,t2;
  char op = 'A';
	int period = 0;

	status stt;
	stt.stream = OFF;
	stt.video = OFF;
	stt.fperiod = OFF;

  init_server();
	while(1) {
	//system("clear");
  	printf("\n+=====================<| Middleware |>=====================+");
		printf("\n| [0]Sair  [1]Stream  [2]Video  [3]Foto  [4]Foto Periodica |\n");
		  printf("+==========================================================+\n");
		printf("| STREAM\t(%s)\t|\n| VIDEO \t(%s)\t|\n| FPERIOD\t(%s)\t|\n+=======================+\n \n(Comando)>> ", (stt.stream == 0)? "\e[31;1mOFF\e[m":"\e[32;1mON\e[m", (stt.video == 0)? "\e[31;1mOFF\e[m":"\e[32;1mON\e[m", (stt.fperiod == 0)? "\e[31;1mOFF\e[m":"\e[32;1mON\e[m");
		scanf("%c", &op);
		switch (op) {
    case '0':
      exit(0);
      break;
    case '1':
			if(stt.stream == OFF) {
	      stream_start();
			} else {
	      stream_stop();
			}
			stt.stream = ++stt.stream % 2;
      break;
    case '2':
			if(stt.video == OFF) {
				video_start();
			} else {
				video_stop();
			}
			stt.video = ++stt.video % 2;
      break;
    case '3':
      photo_imed();
      break;
    case '4':
			if(stt.fperiod == OFF) {
				printf("Periodo: ");
			  scanf("%d", &period);
	    	photo_period_start(period);
			} else {
				photo_period_stop();
			}
			stt.fperiod = ++stt.fperiod % 2;
      break;
    default:
      break;
    }
  }
  return 0;
}

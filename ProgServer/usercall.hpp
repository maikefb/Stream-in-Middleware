// Invoke.h - biblioteca do sistema
#include "invoke.hpp"

/* init_server() - sinaliza para iniciar funcionamento do servidor */
int init_server();
/* init_client() - sinaliza para iniciar funcionamento do cliente */
int init_client();
/* photo_period_start() - tira fotos com periodo de "perid" segundos */
int photo_period_start(unsigned char period);
/* photo_period_stop() - tira fotos com periodo de "perid" segundos */
int photo_period_stop();
/* photo_imed() - Tira uma unica foto  */
int photo_imed();
/* stream_start - inicia o processo de stream */
int stream_start();
/* stream_stop - finaliza o processo de stream */
int stream_stop();

int stream_q();
/* video_start - inicia o processo de video */
int video_start();
/* video_stop - finaliza o processo de video */
int video_stop();

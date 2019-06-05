#include "../System/usercall.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define LARGURA 640
#define ALTURA 480


// g++ invoke.cpp main.cpp -pthread -o midd `pkg-config --cflags --libs opencv`
 int main(int argc, char const *argv[]) {
   init_server();
   char window[] = {"-===<| CAM |>===-"};
   Mat frame = Mat::zeros(ALTURA, LARGURA, CV_8UC3);
   namedWindow(window, WINDOW_NORMAL);
   photo_imed();
   printf ("Ola Mundo  \n\n");
   while (1){
     frame = stream_qt();
     imshow(window,frame);
	photo_imed();
	if (waitKey(30) == 27)
          break;

}
   return 0;
 }

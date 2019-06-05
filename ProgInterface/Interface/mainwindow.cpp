#include "mainwindow.h"
#include "ui_mainwindow.h"


#include "../../System/usercall.hpp"

#define LARGURA 640
#define ALTURA 480

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    emit on_stop();
    delete ui;
}



void MainWindow::newNumber(Mat frame)
{
    ui->lb_img->setPixmap(QPixmap::fromImage(QImage((unsigned char*) frame.data, frame.cols, frame.rows, QImage::Format_RGB888)));

    //qDebug() << "From Dialog";
}

void MainWindow::on_pB_stream_clicked()
{
    /*
    Pega o dado em Qstring e trasforma em Const Char para nos poder verificar utilizando a função qstrcmp no if.
    */
    QString ops;                    //Criando uma variavel "QString" para salvar o nome do botão
    QByteArray inBytes;             //Criando um "Array de bits" chamada "inBytes" para salvar os dados da String
    const char *cops;               //Criando um ponteiro const char chamada de "cops" onde iremos colocar o nome do botão
    ops = ui->pB_stream->text();    //Pegamos o nome do botao "pB_stream" e salvamos na Qstring "ops"
    inBytes = ops.toUtf8();         //Pegamos os dados da Qstring "Ops" e trasformemos para UTF-8 para salvar no "inBytes"
    cops = inBytes.constData();     //Pegamos os bytes e trasformamos para char para guardar no "cops"
   /*******************************/


    if (qstrcmp(cops,"Stream - ON" )  == 0)            //Verifica o nome se for "Stream - ON" Vamos iniciar o Stream
    {
        ui->pB_stream->setText("Stream - OFF");        //Muda o nome do botao para "Stream - OFF" para quando nos clicar novamente ele parar o stream

        /*
        *  Started Stream
        */
            //qRegisterMetaType<cv::Mat>("Mat&");

            //qRegisterNormalizedMetaType<cv::Mat>;

            connect (&mstream,&pStream::qtStream,this,&MainWindow::newNumber);
            connect (this,&MainWindow::on_stop,&mstream,&pStream::stop);

            QFuture<void> test = QtConcurrent::run(&this->mstream,&pStream::start);




    }
    if (qstrcmp(cops,"Stream - OFF" )  == 0)           //Verifica o nome, se for "Stream - OFF" desliga a Stream
    {

        /*
         * Stopped Stream
        */
            emit on_stop();


        /*
        *   Pega o caminho da imagen e o tamanho da label para poder botar a imagen "OFFLINE" na tela
        */
        QPixmap pix (":/resources/img/offline.png");
        int w = ui->lb_img->width();
        int h = ui->lb_img->height();
        /*********************************/
        ui->pB_stream->setText("Stream - ON");                       //Muda o nome do botao para "Stream - ON" para quando nos clicar novamente ele iniciar o stream
        ui->lb_img->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));  //pega a imagen e muda a escala para a que pegamos anteriormente
        /***********************************************************/
    }
}

void MainWindow::on_pB_video_clicked()
{
    /*
    Pega o dado em Qstring e trasforma em Const Char para nos poder verificar utilizando a função qstrcmp no if.
    */
    QString ops;                    //Criando uma variavel "QString" para salvar o nome do botão
    QByteArray inBytes;             //Criando um "Array de bits" chamada "inBytes" para salvar os dados da String
    const char *cops;               //Criando um ponteiro const char chamada de "cops" onde iremos colocar o nome do botão
    ops = ui->pB_video->text();     //Pegamos o nome do botao "pB_video" e salvamos na Qstring "ops"
    inBytes = ops.toUtf8();         //Pegamos os dados da Qstring "Ops" e trasformemos para UTF-8 para salvar no "inBytes"
    cops = inBytes.constData();     //Pegamos os bytes e trasformamos para char para guardar no "cops"
   /*******************************/

    if (qstrcmp(cops,"Video - ON" )  == 0)            //Verifica o nome se for "Video - ON" Vamos iniciar o Stream
    {
        ui->pB_video->setText("Video - OFF");        //Muda o nome do botao para "Video - OFF" para quando nos clicar novamente ele parar o stream
        /*
        *  Iniciar a CAPTURA de video
        */

        video_start();
    }
    if (qstrcmp(cops,"Video - OFF" )  == 0)            //Verifica o nome se for "Video - OFF" Vamos iniciar o Stream
    {
        ui->pB_video->setText("Video - ON");        //Muda o nome do botao para "Video - ON" para quando nos clicar novamente ele parar o stream
        /*
        *   Finalizar a CAPTURA de video
        */
        video_stop();

    }



}

void MainWindow::on_pB_photoI_clicked()
{
    photo_imed();
}



void MainWindow::on_pB_photoP_clicked()
{
    QString num_text = ui->sB_num->text();
       int num = num_text.toInt();
       if (num >= 1){
           photo_period_start(num);
       }
       else{
           photo_period_stop();
       }

}

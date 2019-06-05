#include "pstream.h"
#include "../../../Middleware_UDP_1.1/System/usercall.hpp"

pStream::pStream(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<cv::Mat>("cv::Mat");
    mStop = false;
}

pStream::~pStream()
{

}

void pStream::start()
{
    mStop = false;

    Mat frame = Mat::zeros(ALTURA, LARGURA, CV_8UC3);

    for (;;)
    {
        frame = stream_qt();
        cvtColor(frame, frame, CV_BGR2RGB); //Opencv trabalha com cores BGR já o QT trabalha com cores RGB entao temos que trasformar
        if (mStop) return;
        qDebug() << "From Thread: ";
        emit qtStream(frame);
        //waitKey(10);
        //QThread::currentThread()->msleep(30);
    }
}

void pStream::stop()
{
    mStop = true;
}

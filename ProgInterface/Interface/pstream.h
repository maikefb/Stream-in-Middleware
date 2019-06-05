#ifndef PSTREAM_H
#define PSTREAM_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QMetaType>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


class pStream : public QObject
{
    Q_OBJECT
public:
    explicit pStream(QObject *parent = nullptr);
    ~pStream();

    void start();

signals:

    void qtStream(cv::Mat frame);

public slots:

    void stop();

private:

    bool mStop;

};

#endif // PSTREAM_H

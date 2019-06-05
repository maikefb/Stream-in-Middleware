#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "pstream.h"
#include <QMainWindow>
#include <QThread>
#include <QDebug>
#include <QtConcurrent>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void on_stop();


private slots:
    void on_pB_stream_clicked();

    void on_pB_video_clicked();

    void on_pB_photoI_clicked();

    void on_pB_photoP_clicked();

private:
    Ui::MainWindow *ui;
    pStream mstream;

public slots:

    void newNumber(cv::Mat frame);
};

#endif // MAINWINDOW_H

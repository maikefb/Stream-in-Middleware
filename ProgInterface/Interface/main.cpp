#include "mainwindow.h"
#include <QApplication>
#include "../../../Middleware_UDP_1.1/System/usercall.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    init_server();
    MainWindow w;
    w.show();

    return a.exec();
}

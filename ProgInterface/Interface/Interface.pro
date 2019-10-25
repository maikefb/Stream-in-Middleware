#-------------------------------------------------
#
# Project created by QtCreator 2018-04-20T22:08:24
#
#-------------------------------------------------

QT       += core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Interface
TEMPLATE = app
# Incluindo os Bibliotecas do OpenCV
INCLUDEPATH += .
INCLUDEPATH += /usr/local/include
INCLUDEPATH += /usr/local/include/opencv
INCLUDEPATH += /usr/local/include/opencv2
INCLUDEPATH += /usr/local/include/opencv2/core
INCLUDEPATH += /usr/local/include/opencv2/highgui
INCLUDEPATH += /usr/local/include/opencv2/imgproc
INCLUDEPATH += /usr/local/include/opencv2/flann
INCLUDEPATH += /usr/local/include/opencv2/photo
INCLUDEPATH += /usr/local/include/opencv2/video
INCLUDEPATH += /usr/local/include/opencv2/features2d
INCLUDEPATH += /usr/local/include/opencv2/objdetect
INCLUDEPATH += /usr/local/include/opencv2/calib3d
INCLUDEPATH += /usr/local/include/opencv2/ml
INCLUDEPATH += /usr/local/include/opencv2/contrib
# Outras bibliotecas Utilizadas
LIBS += -pthread `pkg-config opencv --cflags --libs`

# Definições por padrão
DEFINES += QT_DEPRECATED_WARNINGS



# Apagar a linha do invoke.cpp e usercall.cpp para poder configurar novamente
SOURCES += \
        main.cpp \
        mainwindow.cpp \
    ../../System/invoke.cpp \
    ../../System/usercall.cpp \
    pstream.cpp


# Apagar a linha do invoke.hpp e usercall.hpp para poder configurar novamente
HEADERS += \
        mainwindow.h \
    ../../System/invoke.hpp \
    ../../System/usercall.hpp \
    pstream.h


FORMS += \
        mainwindow.ui

RESOURCES += \
    resource.qrc

DISTFILES +=

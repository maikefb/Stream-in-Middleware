/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *lb_img;
    QPushButton *pB_video;
    QPushButton *pB_stream;
    QPushButton *pB_photoP;
    QPushButton *pB_photoI;
    QSpinBox *sB_num;
    QLabel *lb_logo;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(712, 552);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QString::fromUtf8("background: rgb(136, 138, 133)"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        lb_img = new QLabel(centralWidget);
        lb_img->setObjectName(QString::fromUtf8("lb_img"));
        lb_img->setGeometry(QRect(30, 80, 631, 321));
        lb_img->setAutoFillBackground(false);
        lb_img->setPixmap(QPixmap(QString::fromUtf8(":/resources/img/offline.png")));
        lb_img->setScaledContents(true);
        lb_img->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pB_video = new QPushButton(centralWidget);
        pB_video->setObjectName(QString::fromUtf8("pB_video"));
        pB_video->setGeometry(QRect(40, 420, 120, 50));
        pB_stream = new QPushButton(centralWidget);
        pB_stream->setObjectName(QString::fromUtf8("pB_stream"));
        pB_stream->setGeometry(QRect(190, 420, 120, 50));
        pB_photoP = new QPushButton(centralWidget);
        pB_photoP->setObjectName(QString::fromUtf8("pB_photoP"));
        pB_photoP->setGeometry(QRect(490, 420, 120, 50));
        pB_photoP->setAutoFillBackground(false);
        pB_photoI = new QPushButton(centralWidget);
        pB_photoI->setObjectName(QString::fromUtf8("pB_photoI"));
        pB_photoI->setGeometry(QRect(340, 420, 120, 50));
        sB_num = new QSpinBox(centralWidget);
        sB_num->setObjectName(QString::fromUtf8("sB_num"));
        sB_num->setGeometry(QRect(610, 420, 40, 50));
        lb_logo = new QLabel(centralWidget);
        lb_logo->setObjectName(QString::fromUtf8("lb_logo"));
        lb_logo->setGeometry(QRect(500, 10, 201, 61));
        lb_logo->setPixmap(QPixmap(QString::fromUtf8(":/resources/img/uergs-logo.png")));
        lb_logo->setScaledContents(true);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 712, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        statusBar->setAutoFillBackground(false);
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        lb_img->setText(QString());
        pB_video->setText(QApplication::translate("MainWindow", "Video - ON", nullptr));
        pB_stream->setText(QApplication::translate("MainWindow", "Stream - ON", nullptr));
        pB_photoP->setText(QApplication::translate("MainWindow", "Periodic Photo", nullptr));
        pB_photoI->setText(QApplication::translate("MainWindow", "Photo", nullptr));
        lb_logo->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

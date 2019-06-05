/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
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
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(712, 552);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QStringLiteral("background: rgb(136, 138, 133)"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        lb_img = new QLabel(centralWidget);
        lb_img->setObjectName(QStringLiteral("lb_img"));
        lb_img->setGeometry(QRect(30, 80, 631, 321));
        lb_img->setAutoFillBackground(false);
        lb_img->setPixmap(QPixmap(QString::fromUtf8(":/resources/img/offline.png")));
        lb_img->setScaledContents(true);
        lb_img->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pB_video = new QPushButton(centralWidget);
        pB_video->setObjectName(QStringLiteral("pB_video"));
        pB_video->setGeometry(QRect(40, 420, 120, 50));
        pB_stream = new QPushButton(centralWidget);
        pB_stream->setObjectName(QStringLiteral("pB_stream"));
        pB_stream->setGeometry(QRect(190, 420, 120, 50));
        pB_photoP = new QPushButton(centralWidget);
        pB_photoP->setObjectName(QStringLiteral("pB_photoP"));
        pB_photoP->setGeometry(QRect(490, 420, 120, 50));
        pB_photoP->setAutoFillBackground(false);
        pB_photoI = new QPushButton(centralWidget);
        pB_photoI->setObjectName(QStringLiteral("pB_photoI"));
        pB_photoI->setGeometry(QRect(340, 420, 120, 50));
        sB_num = new QSpinBox(centralWidget);
        sB_num->setObjectName(QStringLiteral("sB_num"));
        sB_num->setGeometry(QRect(610, 420, 40, 50));
        lb_logo = new QLabel(centralWidget);
        lb_logo->setObjectName(QStringLiteral("lb_logo"));
        lb_logo->setGeometry(QRect(500, 10, 201, 61));
        lb_logo->setPixmap(QPixmap(QString::fromUtf8(":/resources/img/uergs-logo.png")));
        lb_logo->setScaledContents(true);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 712, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        statusBar->setAutoFillBackground(false);
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        lb_img->setText(QString());
        pB_video->setText(QApplication::translate("MainWindow", "Video - ON", 0));
        pB_stream->setText(QApplication::translate("MainWindow", "Stream - ON", 0));
        pB_photoP->setText(QApplication::translate("MainWindow", "Periodic Photo", 0));
        pB_photoI->setText(QApplication::translate("MainWindow", "Photo", 0));
        lb_logo->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

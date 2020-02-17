/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTreeView *treeView;
    QPushButton *ConnectBut;
    QLabel *label;
    QPushButton *pushButton;
    QLabel *setting1_label;
    QLabel *setting2_label;
    QComboBox *techCombo;
    QComboBox *protoCombo;
    QCheckBox *KillSwitch;
    QCheckBox *CyberSec;
    QCheckBox *ofs;
    QCheckBox *Notify;
    QCheckBox *AutoC;
    QCheckBox *dns;
    QLabel *label_2;
    QTreeView *groups;
    QLabel *titleimage;
    QPushButton *pushButton_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(577, 586);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        treeView = new QTreeView(centralwidget);
        treeView->setObjectName(QString::fromUtf8("treeView"));
        treeView->setGeometry(QRect(20, 40, 231, 281));
        ConnectBut = new QPushButton(centralwidget);
        ConnectBut->setObjectName(QString::fromUtf8("ConnectBut"));
        ConnectBut->setGeometry(QRect(280, 110, 80, 26));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(260, 350, 291, 161));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(380, 110, 80, 26));
        setting1_label = new QLabel(centralwidget);
        setting1_label->setObjectName(QString::fromUtf8("setting1_label"));
        setting1_label->setGeometry(QRect(290, 160, 101, 18));
        setting2_label = new QLabel(centralwidget);
        setting2_label->setObjectName(QString::fromUtf8("setting2_label"));
        setting2_label->setGeometry(QRect(290, 190, 58, 18));
        techCombo = new QComboBox(centralwidget);
        techCombo->setObjectName(QString::fromUtf8("techCombo"));
        techCombo->setGeometry(QRect(400, 160, 111, 26));
        protoCombo = new QComboBox(centralwidget);
        protoCombo->setObjectName(QString::fromUtf8("protoCombo"));
        protoCombo->setGeometry(QRect(400, 190, 111, 26));
        KillSwitch = new QCheckBox(centralwidget);
        KillSwitch->setObjectName(QString::fromUtf8("KillSwitch"));
        KillSwitch->setGeometry(QRect(270, 230, 85, 24));
        CyberSec = new QCheckBox(centralwidget);
        CyberSec->setObjectName(QString::fromUtf8("CyberSec"));
        CyberSec->setGeometry(QRect(430, 230, 85, 24));
        ofs = new QCheckBox(centralwidget);
        ofs->setObjectName(QString::fromUtf8("ofs"));
        ofs->setGeometry(QRect(270, 270, 85, 24));
        Notify = new QCheckBox(centralwidget);
        Notify->setObjectName(QString::fromUtf8("Notify"));
        Notify->setGeometry(QRect(430, 270, 85, 24));
        AutoC = new QCheckBox(centralwidget);
        AutoC->setObjectName(QString::fromUtf8("AutoC"));
        AutoC->setGeometry(QRect(270, 310, 121, 24));
        dns = new QCheckBox(centralwidget);
        dns->setObjectName(QString::fromUtf8("dns"));
        dns->setGeometry(QRect(430, 310, 85, 24));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 10, 241, 31));
        label_2->setMinimumSize(QSize(20, 20));
        QFont font;
        font.setFamily(QString::fromUtf8("Noto Sans Carian"));
        font.setPointSize(16);
        label_2->setFont(font);
        label_2->setTextFormat(Qt::RichText);
        groups = new QTreeView(centralwidget);
        groups->setObjectName(QString::fromUtf8("groups"));
        groups->setGeometry(QRect(20, 320, 231, 201));
        titleimage = new QLabel(centralwidget);
        titleimage->setObjectName(QString::fromUtf8("titleimage"));
        titleimage->setGeometry(QRect(280, 20, 221, 71));
        titleimage->setPixmap(QPixmap(QString::fromUtf8(":/nordvpn.png")));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(480, 110, 80, 26));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 577, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "NordVPN Front-End", nullptr));
        ConnectBut->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Disconect", nullptr));
        setting1_label->setText(QCoreApplication::translate("MainWindow", "Technology", nullptr));
        setting2_label->setText(QCoreApplication::translate("MainWindow", "Protocol", nullptr));
        KillSwitch->setText(QCoreApplication::translate("MainWindow", "Kill Switch", nullptr));
        CyberSec->setText(QCoreApplication::translate("MainWindow", "CyberSec", nullptr));
        ofs->setText(QCoreApplication::translate("MainWindow", "Ofuscate", nullptr));
        Notify->setText(QCoreApplication::translate("MainWindow", "Notify", nullptr));
        AutoC->setText(QCoreApplication::translate("MainWindow", "Auto Connect", nullptr));
        dns->setText(QCoreApplication::translate("MainWindow", "DNS", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Select Server Location", nullptr));
        titleimage->setText(QString());
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Logout", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

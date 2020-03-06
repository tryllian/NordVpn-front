#include <QApplication>
#include <QMessageBox>

#include "mainwindow.h"
#include "login.h"
#include "vpaanctions.h"


int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(nordvpnfront);

    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/nordvpnicon.png"));
    vpaanctions *Actions = new vpaanctions();

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(nullptr, QObject::tr("Systray"),
                              QObject::tr("I couldn't detect any system tray "
                                          "on this system."));
        return 1;
    }
    QApplication::setQuitOnLastWindowClosed(false);


    Login l;
    MainWindow w;


    if (Actions->CheckLogin())
    {

        w.show();
    }
        else
        l.show();

    Actions = new vpaanctions;
    delete Actions;
    Actions = NULL;



    return a.exec();
}

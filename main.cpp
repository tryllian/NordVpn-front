#include "mainwindow.h"
#include "login.h"
#include <QApplication>
#include "vpaanctions.h"


int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(nordvpnfront);

    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("./nordvpnicon.png"));
    vpaanctions *Actions = new vpaanctions();


    Login l;
    MainWindow w;

    if (Actions->CheckLogin())
        w.show();
    else
        l.show();

    Actions = new vpaanctions;
    delete Actions;
    Actions = NULL;



    return a.exec();
}

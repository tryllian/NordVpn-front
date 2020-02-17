#include "login.h"
#include "ui_login.h"
#include "vpaanctions.h"
#include "mainwindow.h"

#include <QMessageBox>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    ui->Uname->setStyleSheet("QLineEdit { background-color: white; color:black;}");
    ui->Upassword->setStyleSheet("QLineEdit { background-color: white; color:black;}");

}

Login::~Login()
{
    delete ui;
}



void Login::on_pushButton_2_clicked()
{
    close();
    qApp->quit();
}

void Login::on_pushButton_clicked()
{
    vpaanctions *Actions = new vpaanctions();
    bool result = Actions->Login(ui->Uname->text(),ui->Upassword->text());
    Actions = new vpaanctions;
    delete Actions;
    Actions = NULL;

    if (result)
    {

        MainWindow *m = new MainWindow();
        m->show();
        close();
     }
    else
    {
        QMessageBox::about(this, tr("Login Error"),
                tr("User Name or Password Incorrect."));
    }
}

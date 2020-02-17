#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "login.h"
#include "licence.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->techCombo->addItem("OpenVPN","OpenVPN");
    ui->techCombo->addItem("NordLynx","NordLynx");
    ui->protoCombo->addItem("TCP","TCP");
    ui->protoCombo->addItem("UDP","UDP");
    Actions = new vpaanctions();

    QStandardItemModel *settings = Actions->GetSettings();
    model = Actions->GetLocations();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),
              this, SLOT(activetimer()));

    timer->start(30000);
    ui->treeView->setModel(model);
    setupSettings(settings);
    setupStatus(Actions->GetStatus());
    ui->groups->setModel(Actions->GetGroups());
   // QPixmap  mypix(":/home/tryllian/projects/Nordvpn-front/nordvpn.png");
    //ui->Titleimage->setPixmap(mypix);
    //delete mypix;
    createActions();
    createMenus();




}

void MainWindow::createActions()
{
        exitAct = new QAction(tr("E&xit"), this);
        exitAct->setShortcuts(QKeySequence::Quit);
        exitAct->setStatusTip(tr("Exit the application"));
        connect(exitAct, &QAction::triggered, this, &QWidget::close);

        aboutAct = new QAction(tr("&About"), this);
        aboutAct->setStatusTip(tr("Show the application's About box"));
        connect(aboutAct, &QAction::triggered, this, &MainWindow::about);

        aboutQtAct = new QAction(tr("Licence"), this);
        aboutQtAct->setStatusTip(tr("Licence Information"));
        connect(aboutQtAct, &QAction::triggered, this, &MainWindow::aboutQt);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);


    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

void MainWindow::about()
{
    //infoLabel->setText(tr("Invoked <b>Help|About</b>"));
    auto dialog = new Dialog();
    dialog->show();
}

void MainWindow::aboutQt()
{

    auto dialog = new Licence();
    dialog->show();
    //infoLabel->setText(tr("Invoked <b>Help|About Qt</b>"));
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::forEach(QAbstractItemModel* model, QModelIndex parent) {
    for(int r = 0; r < model->rowCount(parent); ++r) {
        QModelIndex index = model->index(r, 0, parent);
        QVariant name = model->data(index);
        qDebug() << name;
        // here is your applicable code
        if( model->hasChildren(index) ) {
            forEach(model, index);
        }
    }
}


void MainWindow::setupStatus(QStandardItemModel* status){
    auto viewmodel = ui->treeView->model();

    if (status->item(0,1)->text().trimmed() != "Disconnected")
    {
    QString item = status->item(3,1)->text().trimmed();
    item.replace(' ','_');
    //forEach(viewmodel);
   //
   //QStandardItemModel test =  ui->tableView->model();
  auto items = model->findItems(item,Qt::MatchRecursive,0);
    if (!items.empty()) {
           auto index = items.first()->index();
            ui->treeView->setCurrentIndex(index);
       }
}
}


void MainWindow::setupSettings(QStandardItemModel* settings)
{
    //vpaanctions Actions;
    ui->label->setText(Actions->Status()) ;
    QString test = settings->item(0,0)->text() ;
    if (test=="A new version of NordVPN is available! Please update the application.")
    {
        QMessageBox::about(this, tr("About Menu"),
                tr("A new version of NordVPN is available! Please update the application. Please install and restart NordVpn Front"));
        close();
        qApp->quit();
    }
    else
    {
    if (settings->rowCount()==6)

    {
        ui->protoCombo->setEnabled(false);
        ui->ofs->setEnabled(false);

        int index = ui->techCombo->findData(settings->item(0,1)->text());
        if ( index != -1 ) { // -1 for not found
            ui->techCombo->setCurrentIndex(index);
        }
        if (settings->item(1,1)->text()=="enabled")
            ui->KillSwitch->setChecked(1);
        if (settings->item(2,1)->text()=="enabled")
            ui->CyberSec->setChecked(1);

        if (settings->item(3,1)->text()=="enabled")
            ui->Notify->setChecked(1);
        if (settings->item(4,1)->text()=="enabled")
            ui->AutoC->setChecked(1);
        if (settings->item(5,1)->text()=="enabled")
            ui->dns->setChecked(1);

    }
    else
    {

        ui->protoCombo->setDisabled(false);
        ui->ofs->setDisabled(false);
    int index = ui->techCombo->findData(settings->item(0,1)->text());
    if ( index != -1 ) { // -1 for not found
        ui->techCombo->setCurrentIndex(index);
    }


    index = ui->protoCombo->findData(settings->item(1,1)->text());
    if ( index != -1 ) { // -1 for not found
        ui->protoCombo->setCurrentIndex(index);
    }


    if (settings->item(2,1)->text()=="enabled")
        ui->KillSwitch->setChecked(1);
    if (settings->item(3,1)->text()=="enabled")
        ui->CyberSec->setChecked(1);
    if (settings->item(4,1)->text()=="enabled"){
        ui->ofs->setChecked(1);}
    if (settings->item(5,1)->text()=="enabled")
        ui->Notify->setChecked(1);
    if (settings->item(6,1)->text()=="enabled")
        ui->AutoC->setChecked(1);
    if (settings->item(7,1)->text()=="enabled")
        ui->dns->setChecked(1);
    }
   //
    }
}


void MainWindow::on_ConnectBut_clicked()
{
    QMessageBox msgBox;
    QModelIndex index = ui->treeView->selectionModel()->currentIndex();
   // QAbstractItemModel *modelview = ui->treeView->model();
    auto *modelview = ui->treeView->model();

    if (!index.parent().isValid())
        {
        Actions->Connect(modelview->data(index.parent(),0).toString() + " " + model->data(index,0).toString());
        }
    else{
        Actions->Connect(modelview->data(index,0).toString());
    }
    msgBox.setText(Actions->Status());

            msgBox.exec();
    ui->label->setText(Actions->Status()) ;
}

void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{

    QMessageBox msgBox;
    //QModelIndex index = ui->treeView->selectionModel()->currentIndex();
   // QAbstractItemModel *modelview = ui->treeView->model();
    auto *modelview = ui->treeView->model();

    if (!index.parent().isValid())
        {
        Actions->Connect(modelview->data(index.parent(),0).toString() + " " + model->data(index,0).toString());
        }
    else{
        Actions->Connect(modelview->data(index,0).toString());
    }
    msgBox.setText(Actions->Status());

            msgBox.exec();
    ui->label->setText(Actions->Status()) ;
}

void MainWindow::on_pushButton_clicked()
{
    QMessageBox msgBox;

    Actions->disConnect();
    msgBox.setText(Actions->Status());

            msgBox.exec();
            ui->label->setText(Actions->Status()) ;
}

void MainWindow::activetimer()
{

     QStandardItemModel *settings = Actions->GetSettings();
    setupSettings(settings);
}










void MainWindow::on_techCombo_activated(const QString &arg1)
{
    QMessageBox msgBox;

    msgBox.setText(Actions->SetSettings(arg1,"technology"));
   msgBox.exec();
   setupSettings(Actions->GetSettings());
}

void MainWindow::on_protoCombo_activated(const QString &arg1)
{
    QMessageBox msgBox;

    msgBox.setText(Actions->SetSettings(arg1,"protocol"));
    msgBox.exec();
}



void MainWindow::on_KillSwitch_clicked(bool checked)
{

    QMessageBox msgBox;


    QString reply;
    //qDebug() << "Hello from this file" << arg1;
    if (checked){
        reply = Actions->SetSettings("true","killswitch");
    }else
    {
         reply = Actions->SetSettings("false","killswitch");
    }

    msgBox.setText(reply);

    msgBox.exec();
}

void MainWindow::on_CyberSec_clicked(bool checked)
{
    QMessageBox msgBox;


    QString reply;
    //qDebug() << "Hello from this file" << arg1;
    if (checked){
        reply = Actions->SetSettings("true","cybersec");
    }else
    {
         reply = Actions->SetSettings("false","cybersec");
    }

    msgBox.setText(reply);

    msgBox.exec();
}

void MainWindow::on_ofs_clicked(bool checked)
{

    QMessageBox msgBox;


    QString reply;
    //qDebug() << "Hello from this file" << arg1;
    if (checked){
        reply = Actions->SetSettings("true","obfuscate");
    }else
    {
         reply = Actions->SetSettings("false","obfuscate");
    }

    msgBox.setText(reply);

    msgBox.exec();
}

void MainWindow::on_Notify_clicked(bool checked)
{

    QMessageBox msgBox;


    QString reply;
    //qDebug() << "Hello from this file" << arg1;
    if (checked){
        reply = Actions->SetSettings("true","notify");
    }else
    {
         reply = Actions->SetSettings("false","notify");
    }

    msgBox.setText(reply);

    msgBox.exec();
}

void MainWindow::on_AutoC_clicked(bool checked)
{

    QMessageBox msgBox;


    QString reply;
    //qDebug() << "Hello from this file" << arg1;
    if (checked){
        reply = Actions->SetSettings("true","autoconnect");
    }else
    {
         reply = Actions->SetSettings("false","autoconnect");
    }

    msgBox.setText(reply);

    msgBox.exec();
}

void MainWindow::on_dns_clicked(bool checked)
{

    QMessageBox msgBox;


    QString reply;
    //qDebug() << "Hello from this file" << arg1;
    if (checked){
        reply = Actions->SetSettings("true","autoconnect");
    }else
    {
         reply = Actions->SetSettings("false","autoconnect");
    }

    msgBox.setText(reply);

    msgBox.exec();
}

void MainWindow::on_groups_doubleClicked(const QModelIndex &index)
{
    QMessageBox msgBox;
    //QModelIndex index = ui->treeView->selectionModel()->currentIndex();
   // QAbstractItemModel *modelview = ui->treeView->model();
    auto *modelview = ui->groups->model();


        Actions->Connect(modelview->data(index,0).toString());

    msgBox.setText(Actions->Status());

            msgBox.exec();
    ui->label->setText(Actions->Status()) ;
     setupStatus(Actions->GetStatus());
}

void MainWindow::on_pushButton_2_clicked()
{
    bool result = Actions->Logout();



    if (result)
    {
        QMessageBox::about(this, tr("Logout Success"),
                tr("You have been Logout returng to the Login screen"));
        //close();
        Login *m = new Login();
        m->show();
        close();
     }
    else
    {
        QMessageBox::about(this, tr("Logout Error"),
                tr("Your were not logout"));
    }
}

#include <QCloseEvent>
#include <QSettings>
#include <QFile>
#include <QStandardItem>
#include <QMessageBox>
#include <QTreeWidgetItem>
#include <QtDebug>
#include <QTimer>
#include <QStandardPaths>


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "login.h"
#include "licence.h"
#include "mainwindow.h"


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

    m_sSettingsFile = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/NordVpn-Front/settings.ini";
    loadSettings();



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
    createTrayActions();
    createTrayIcon();

    //recentVpns = new QStringList();
    updateRecentFileActions();
    ui->treeView->installEventFilter(this);
    trayIcon->setIcon(QIcon(":/nordvpnicon.png"));
    trayIcon->show();



}

void MainWindow::closeEvent(QCloseEvent *event)
{
#ifdef Q_OS_OSX
    if (!event->spontaneous() || !isVisible()) {
        return;
    }
#endif
    if (trayIcon->isVisible()) {
        QMessageBox::information(this, tr("Systray"),
                                 tr("The program will keep running in the "
                                    "system tray. To terminate the program, "
                                    "choose <b>Quit</b> in the context menu "
                                    "of the system tray entry."));
        hide();
        event->ignore();
    }
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
    QString location ;
    QModelIndex index = ui->treeView->selectionModel()->currentIndex();
   // QAbstractItemModel *modelview = ui->treeView->model();
    auto *modelview = ui->treeView->model();

    if (index.parent().isValid())
        {
            location = modelview->data(index.parent(),0).toString() + " " + model->data(index,0).toString();
        }
    else
        {
            location =  modelview->data(index,0).toString();
        }

    Actions->Connect(location);
    updateRecentVpns(location);
    msgBox.setText(Actions->Status());

            msgBox.exec();
    ui->label->setText(Actions->Status()) ;
    updateRecentFileActions();

}

void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{

    QMessageBox msgBox;
    QString location;
    //QModelIndex index = ui->treeView->selectionModel()->currentIndex();
   // QAbstractItemModel *modelview = ui->treeView->model();
    auto *modelview = ui->treeView->model();

    if (index.parent().isValid())
        {
            location = modelview->data(index.parent(),0).toString() + " " + model->data(index,0).toString();
        }
    else
        {
            location = modelview->data(index,0).toString();
        }

    Actions->Connect(location);
    updateRecentVpns(location);
    qDebug() << "Hello from this file" << location;

    msgBox.setText(Actions->Status());

            msgBox.exec();
    ui->label->setText(Actions->Status()) ;
    updateRecentFileActions();
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

void MainWindow::createTrayActions()
{
    minimizeAction = new QAction(tr("Mi&nimize"), this);
    connect(minimizeAction, &QAction::triggered, this, &QWidget::hide);

    maximizeAction = new QAction(tr("Ma&ximize"), this);
    connect(maximizeAction, &QAction::triggered, this, &QWidget::showMaximized);

    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, &QAction::triggered, this, &QWidget::showNormal);

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

    connectFav = new QAction(tr("&Connect"), this);
    connectFav->setData("aasdasd");
   // connect(connectFav, &QAction::triggered, this, SLOT(&MainWindow::aboutQt));
    connect(connectFav, &QAction::triggered, this, &MainWindow::conectFavorites);

    for (int i = 0; i < MaxRecentFiles; ++i) {
            menuFavActs[i] = new QAction(this);
            menuFavActs[i]->setVisible(false);
            connect(menuFavActs[i], &QAction::triggered,this, &MainWindow::conectFavorites);
        }


}

void MainWindow::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addSection("Recent Vpns");
    for (int i = 0; i < MaxRecentFiles; ++i)
            trayIconMenu->addAction(menuFavActs[i]);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
    QMainWindow::setVisible(false);
}

void MainWindow::setVisible(bool visible)
{
    minimizeAction->setEnabled(visible);
    maximizeAction->setEnabled(!isMaximized());
    restoreAction->setEnabled(isMaximized() || !visible);
    QMainWindow::setVisible(visible);
}


void MainWindow::conectFavorites(){
       QMessageBox msgBox;
    QAction *action = qobject_cast<QAction *>(sender());
    QString location = action->data().toString();
    Actions->Connect(location);
    //updateRecentVpns(location);
    msgBox.setText(Actions->Status());

            msgBox.exec();
    ui->label->setText(Actions->Status()) ;
}

void MainWindow::updateRecentVpns(QString location)
{
    int numRecentVpns = recentVpns.size();
    bool found = false;

    for (int i = 0; i < numRecentVpns; ++i)
    {
        if (recentVpns.value(i) == location)
        {
            recentVpns.removeAt(i);
            found = true;
        }
    }
    if (numRecentVpns == 5 )
    {

         if (!found)
            recentVpns.removeLast();

    }
    recentVpns.insert(0,location);
    saveSettings();
}

void MainWindow::loadSettings()
{
 QString test;
 QSettings settings(m_sSettingsFile, QSettings::IniFormat);
 QString firstload = settings.value("firstload").toString();

 if (firstload=="")
 {
     qDebug() << "First load";
 }
 //settings.setValue("recentVpns", recentVpns);
 recentVpns = settings.value("recentVpns").toStringList();

 //qDebug() << "value " << test;
}

void MainWindow::saveSettings()
{
 QString test;
 QSettings settings(m_sSettingsFile, QSettings::IniFormat);


  settings.setValue("recentVpns", recentVpns);
 test = settings.value("recentVpns").toString();

 //qDebug() << "value " << test;
}

void MainWindow::updateRecentFileActions()
{
    QSettings settings;
    //QStringList files = settings.value("recentFileList").toStringList();

    int numRecentFiles = recentVpns.size();

    for (int i = 0; i < numRecentFiles; ++i) {
        //QString text = tr("&%1 %2").arg(i + 1).arg(strippedName(files[i]));
        menuFavActs[i]->setText(recentVpns.value(i).replace('_',' '));
        menuFavActs[i]->setData(recentVpns.value(i));
        menuFavActs[i]->setVisible(true);
    }
   //for (int j = numRecentFiles; j < MaxRecentFiles; ++j)
    //    recentFileActs[j]->setVisible(false);

   // separatorAct->setVisible(numRecentFiles > 0);
}

bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
    if (target == ui->treeView)
    {
        QContextMenuEvent* m = dynamic_cast<QContextMenuEvent*>(event);
        if (event->type() == QEvent::ContextMenu)
        {
                //Create context menu here
                return true;
        }
    }
    return false;
}




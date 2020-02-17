#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "vpaanctions.h"


#include <QMainWindow>
#include <QFile>
#include <QStandardItem>
#include <QMessageBox>
#include <QTreeWidgetItem>
#include <QtDebug>
#include <QTimer>
#include <QActionGroup>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setupSettings(QStandardItemModel *settings);
    void setupStatus(QStandardItemModel *status);

    void forEach(QAbstractItemModel *model, QModelIndex parent = QModelIndex());
    QTimer *timer;
    void createActions();
    void createMenus();
    void about();
    void aboutQt();
public slots:
        void activetimer();
private slots:
    void on_ConnectBut_clicked();

    void on_treeView_doubleClicked(const QModelIndex &index);

    void on_pushButton_clicked();






    void on_techCombo_activated(const QString &arg1);

    void on_protoCombo_activated(const QString &arg1);


    void on_KillSwitch_clicked(bool checked);

    void on_CyberSec_clicked(bool checked);

    void on_ofs_clicked(bool checked);

    void on_Notify_clicked(bool checked);

    void on_AutoC_clicked(bool checked);

    void on_dns_clicked(bool checked);



    void on_groups_doubleClicked(const QModelIndex &index);

    void on_pushButton_2_clicked();

private:

    Ui::MainWindow *ui;
    QStandardItemModel *model;
    vpaanctions *Actions;
    QMenu *fileMenu;
        QMenu *editMenu;
        QMenu *formatMenu;
        QMenu *helpMenu;
        QActionGroup *alignmentGroup;
        QAction *newAct;
        QAction *openAct;
        QAction *saveAct;
        QAction *printAct;
        QAction *exitAct;
        QAction *undoAct;
        QAction *redoAct;
        QAction *cutAct;
        QAction *copyAct;
        QAction *pasteAct;
        QAction *boldAct;
        QAction *italicAct;
        QAction *leftAlignAct;
        QAction *rightAlignAct;
        QAction *justifyAct;
        QAction *centerAct;
        QAction *setLineSpacingAct;
        QAction *setParagraphSpacingAct;
        QAction *aboutAct;
        QAction *aboutQtAct;
};
#endif // MAINWINDOW_H

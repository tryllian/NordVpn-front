#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "vpaanctions.h"
#include <QMainWindow>

#include <QActionGroup>
#include <QSystemTrayIcon>



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
    void setVisible(bool visible) override;
    void saveSettings();

protected:
    void closeEvent(QCloseEvent *event) override;
    bool eventFilter(QObject *target, QEvent *event) override;

    void updateRecentFileActions();
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
    QMenu *helpMenu;
    QAction *exitAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;
    QAction *connectFav;
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    QString m_sSettingsFile;
    void createTrayIcon();
    void createActions();
    void createMenus();
    void about();
    void aboutQt();
    void createTrayActions();
    void conectFavorites();


    enum { MaxRecentFiles = 5 };
       QAction *menuFavActs[MaxRecentFiles];
       QAction *menuRecActs[MaxRecentFiles];
       QStringList recentVpns;
       QStringList *favVpns;
       void updateRecentVpns(QString location);

       void loadSettings();
};
#endif // MAINWINDOW_H

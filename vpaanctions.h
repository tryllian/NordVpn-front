#ifndef VPAANCTIONS_H
#define VPAANCTIONS_H

#include <QObject>
#include <QProcess>
#include <QStandardItem>

class vpaanctions
{
public:
    vpaanctions();

    void Connect(QString location);
    void disConnect();
    QString Status();
    QString DisplaySettings();
    QStandardItemModel* GetSettings();
    QString SetSettings(QString set, QString Action);
    QStandardItemModel *GetStatus();
    QStandardItemModel *GetLocations();
    QStandardItemModel *GetGroups();
    bool CheckLogin();
    bool Login(QString Uname, QString Upassword);
    bool Logout();
private:
QProcess *m_process;
QString m_AppName;
};

#endif // VPAANCTIONS_H

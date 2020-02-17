#include "vpaanctions.h"




vpaanctions::vpaanctions()
{

}


QString vpaanctions::SetSettings(QString set,QString Action)
{
     QProcess action;
    action.start("nordvpn set " + Action + " " + set);
   //m_process->execute("nordvpn connect " + location) ;
    if (!action.waitForFinished())
            return "false";

    return action.readAll().simplified();

}

void vpaanctions::Connect(QString location)
{
    m_process->execute("nordvpn disconnect");
    m_process->execute("nordvpn connect " + location) ;
}

bool vpaanctions::CheckLogin()
{
    QProcess action;
    action.start("nordvpn account");

    if (!action.waitForFinished())
            return "false";

    QString results = action.readAll();
    results = results.simplified();
    results.replace("- ", "");
    if (results == "You are not logged in.")
        return false;
    else
        return true;

}

bool vpaanctions::Login(QString Uname, QString Upassword)
{
    QProcess action;
    action.start("nordvpn login -u " + Uname +" -p " + Upassword);

    if (!action.waitForFinished())
            return "false";

    QString results = action.readAll();
    results = results.simplified();
    results.replace("- ", "");
    if (results.contains("Welcome to NordVPN!"))
        return true;
    else
        return false;

}

bool vpaanctions::Logout()
{
    QProcess action;
    action.start("nordvpn logout");

    if (!action.waitForFinished())
            return "false";

    QString results = action.readAll();
    results = results.simplified();
    results.replace("- ", "");
    if (results.contains("You are logged out"))
        return true;
    else
        return false;

}

QString vpaanctions::Status()
{
    QProcess action;
    action.start("nordvpn status");

    if (!action.waitForFinished())
            return "false";

    return action.readAll();
}


QString vpaanctions::DisplaySettings()
{
    QProcess action;
    action.start("nordvpn settings");

    if (!action.waitForFinished())
            return "false";

    return action.readAll();
}

QStandardItemModel* vpaanctions::GetGroups()
{
    QStandardItemModel* model = new QStandardItemModel();
    QString settings;
    QProcess action;
    action.start("nordvpn groups");

    if (!action.waitForFinished())
            return model;

    settings = action.readAll();

    settings = settings.simplified();
    settings.replace("-", "");
    QStringList settingStrings = settings.split(',', QString::SkipEmptyParts);
    for (const QString &settingString : settingStrings)
    {
        QString item = settingString.trimmed();
        QStandardItem* mainitem = new QStandardItem(item);
        model->appendRow(mainitem);
    }
    model->setHeaderData(0, Qt::Horizontal, "Groups(Double Click to Connect)");
    return model;
}



QStandardItemModel* vpaanctions::GetLocations()
{
    QStandardItemModel* model = new QStandardItemModel();
    QString settings;
    QProcess action;
    action.start("nordvpn countries");

    if (!action.waitForFinished())
            return model;

    settings = action.readAll();

    settings = settings.simplified();
    settings.replace("-", "");
    QStringList settingStrings = settings.split(',', QString::SkipEmptyParts);
    for (const QString &settingString : settingStrings)
    {
        QString item = settingString.trimmed();
        QStandardItem* mainitem = new QStandardItem(item);
        model->appendRow(mainitem);

        action.start("nordvpn cities " + item);
        if (!action.waitForFinished())
                return model;

        QString cities = action.readAll();

        cities = cities.simplified();
        cities.replace("-", "");
         QStringList cityStrings = cities.split(',', QString::SkipEmptyParts);
         for (const QString &cityString : cityStrings)
         {
             QString item = cityString.trimmed();
             QStandardItem* countitem = new QStandardItem(item);
             mainitem->appendRow(countitem);
         }
    }
    model->setHeaderData(0, Qt::Horizontal, "Countries and Cities");
    return model;
}


QStandardItemModel* vpaanctions::GetSettings()
{
    QStandardItemModel* model = new QStandardItemModel();
    QString settings;
    QProcess action;
    action.start("nordvpn settings");

    if (!action.waitForFinished())
            return model;

    settings = action.readAll();
    settings = settings.replace("\r-\r  \r", "");

    if (!settings.contains("A new Version"))
    {

    QStringList settingStrings = settings.split('\n', QString::SkipEmptyParts);
    for (const QString &settingString : settingStrings)
    {
        const QStringList valueitems = settingString.split(':',QString::SkipEmptyParts);
         QList<QStandardItem *> items;
        for (const QString &valueitem : valueitems)
        {
            QString item = valueitem;

           items.append(new QStandardItem(item.trimmed()));

        }

        model->appendRow(items);
        items.clear();
    }
    }
    return model;
}

QStandardItemModel* vpaanctions::GetStatus()
{
    QStandardItemModel* model = new QStandardItemModel();
    QString settings;
    QProcess action;
    action.start("nordvpn status");

    if (!action.waitForFinished())
            return model;

    settings = action.readAll();
     settings = settings.replace("\r-\r  \r", "");
    QStringList settingStrings = settings.split('\n', QString::SkipEmptyParts);
    for (const QString &settingString : settingStrings)
    {
        const QStringList valueitems = settingString.split(':',QString::SkipEmptyParts);
         QList<QStandardItem *> items;
        for (const QString &valueitem : valueitems)
        {
            QString item = valueitem;
           items.append(new QStandardItem(item.trimmed()));

        }

        model->appendRow(items);
        items.clear();
    }

    return model;
}



void vpaanctions::disConnect()
{
    m_process->execute("nordvpn disconnect");
}

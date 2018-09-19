#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QWidget>
#include <QDebug>
#include <vector>

struct client
{
    QString name;
    QString surname;
    QString address;
    QString zip;
    QString city;
    QString phone;
    QString email;
};

class ClientManager : public QWidget
{
    Q_OBJECT
public:
    explicit ClientManager(QWidget *parent = nullptr);

    void saveClients(std::vector<client>& clients);
    void loadClients(std::vector<client>& clients);
signals:

public slots:

private:

    const QString FILE_NAME = "client.json";
};

#endif // CLIENTMANAGER_H

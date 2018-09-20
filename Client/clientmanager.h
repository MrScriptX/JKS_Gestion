#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QWidget>
#include <QVBoxLayout>
#include <QStringListModel>
#include <QListView>
#include <QPushButton>
#include <QDebug>
#include <vector>
#include <memory>


enum class Client
{
    FETCH_CLIENT,
    VIEW_CLIENT
};

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

    void viewer(Client usage, std::shared_ptr<client> holder = nullptr);
    void saveClient(client& c);
signals:

public slots:
    void selectClient( std::vector<client> clients, std::shared_ptr<client> holder, const QModelIndex& index);

private:

    const QString FILE_NAME = "client.json";
    QListView* m_view;
};

#endif // CLIENTMANAGER_H

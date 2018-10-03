#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QWidget>
#include <QLineEdit>
#include <QTableView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QStringList>
#include <QHeaderView>
#include <QTableWidget>
#include <QStandardItem>
#include <QStandardItemModel>
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

    void tableViewer();
    void clientSelector(std::shared_ptr<client> holder);
    void saveClient(client& c);
    void saveClient(std::vector<client> clients);
signals:
    void clientSelected();

public slots:
    void selectClient( std::vector<client> clients, std::shared_ptr<client> holder, const QModelIndex& index);
    void searchClient(const QString& name, QStringListModel* model);

private:

    const QString FILE_NAME = "client.json";
    QListView* m_view;
    std::vector<client> m_clients;
};

#endif // CLIENTMANAGER_H

#include "clientmanager.h"


ClientManager::ClientManager(QWidget *parent) : QWidget(parent)
{

}

void ClientManager::saveClients(std::vector<client>& clients)
{
    QFile file(FILE_NAME);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qDebug() << "Failed to open client file for writing!";
    }

    QJsonObject object;
    for(uint i = 0; i < clients.size(); i++)
    {
        QString id = QString::number(i);
        QJsonObject json;
        json["name"] = clients[i].name;
        json["surname"] = clients[i].surname;
        json["address"] = clients[i].address;
        json["zip"] = clients[i].zip;
        json["city"] = clients[i].city;
        json["phone"] = clients[i].phone;
        json["email"] = clients[i].email;

        object[id] = json;
    }

    QJsonDocument document(object);
    file.write(document.toJson());

    file.close();
}

void ClientManager::loadClients(std::vector<client>& clients)
{
    QFile file(FILE_NAME);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Failed to open client file for reading !";
    }

    QByteArray raw_data = file.readAll();
    QJsonDocument document = QJsonDocument::fromJson(raw_data);
    QJsonObject object = document.object();


    for(size_t i = 0; i < 100; i++)
    {
        client client;
        QString id = QString::number(i);

        if(object.contains(id) && object[id].isObject())
        {
            QJsonObject json = object[id].toObject();
            if(json.contains("name") && json["name"].isString())
            {
                client.name = json["name"].toString();
            }

            if(json.contains("surname") && json["surname"].isString())
            {
                client.surname = json["surname"].toString();
            }

            if(json.contains("address") && json["address"].isString())
            {
                client.address = json["address"].toString();
            }

            if(json.contains("zip") && json["zip"].isString())
            {
                client.zip = json["zip"].toString();
            }

            if(json.contains("city") && json["city"].isString())
            {
                client.city = json["city"].toString();
            }

            if(json.contains("phone") && json["phone"].isString())
            {
                client.phone = json["phone"].toString();
            }

            if(json.contains("email") && json["email"].isString())
            {
                client.email = json["email"].toString();
            }
        }
        else
        {
            break;
        }

        clients.push_back(client);
    }

    file.close();
}

void ClientManager::tableViewer()
{
    std::vector<client> clients;
    loadClients(clients);

    QTableView* tableView = new QTableView;
    QStandardItemModel* model = new QStandardItemModel;

    for(size_t i = 0; i < clients.size(); i++)
    {
        QStandardItem* name = new QStandardItem;
        name->setText(clients[i].surname + " " + clients[i].name);
        name->setEditable(false);
        model->setItem(static_cast<int>(i), 0, name);

        QStandardItem* tel = new QStandardItem;
        tel->setText(clients[i].phone);
        tel->setEditable(false);
        model->setItem(static_cast<int>(i), 1, tel);

        QStandardItem* address = new QStandardItem;
        address->setText(clients[i].address + " " + clients[i].city);
        address->setEditable(false);
        model->setItem(static_cast<int>(i), 2, address);
    }


    tableView->setModel(model);
    tableView->resizeRowsToContents();
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->setMinimumSize(800, 200);
    tableView->setFocus();
    tableView->show();
}

void ClientManager::clientSelector(std::shared_ptr<client> holder)
{
    std::vector<client> clients;
    loadClients(clients);

    QStringList name_list;
    for(size_t i = 0; i < clients.size(); i++)
    {
        name_list.push_back(clients[i].surname + " " + clients[i].name);
    }

    QStringListModel* model = new QStringListModel;
    model->setStringList(name_list);

    m_view = new QListView;
    m_view->setModel(model);
    connect(m_view, &QListView::doubleClicked, this, [this, clients, holder](const QModelIndex& index){ this->selectClient(clients, holder, index); });

    QLineEdit* search_bar = new QLineEdit;
    QPushButton* search_button = new QPushButton("Find");
    connect(search_button, &QPushButton::clicked, this, [this, search_bar, model]{this->searchClient(search_bar->text(), model);});

    QVBoxLayout* wrapper = new QVBoxLayout;
    wrapper->addWidget(m_view);
    wrapper->addWidget(search_bar);
    wrapper->addWidget(search_button);

    setLayout(wrapper);
    show();
}

void ClientManager::selectClient( std::vector<client> clients, std::shared_ptr<client> holder, const QModelIndex& index)
{
    holder->name = clients[static_cast<size_t>(index.row())].name;
    holder->surname = clients[static_cast<size_t>(index.row())].surname;
    holder->address = clients[static_cast<size_t>(index.row())].address;
    holder->city = clients[static_cast<size_t>(index.row())].city;
    holder->email = clients[static_cast<size_t>(index.row())].email;
    holder->phone = clients[static_cast<size_t>(index.row())].phone;
    holder->zip = clients[static_cast<size_t>(index.row())].zip;

    qDebug() << "client " + holder->name;

    emit clientSelected();

    close();
}

void ClientManager::searchClient(const QString& name, QStringListModel* model)
{
    QStringList unordered_list;
    unordered_list = model->stringList();

    QStringList ordered_list;

    for(size_t i = 0; i < static_cast<size_t>(unordered_list.size()); i++)
    {
        if(unordered_list[static_cast<int>(i)].contains(name, Qt::CaseInsensitive))
        {
            ordered_list.push_front(unordered_list[static_cast<int>(i)]);
        }
        else
        {
            ordered_list.push_back(unordered_list[static_cast<int>(i)]);
        }
    }

    model->setStringList(ordered_list);
}

void ClientManager::saveClient(client& c)
{
    std::vector<client> clients;
    loadClients(clients);

    clients.push_back(c);
    saveClients(clients);
}

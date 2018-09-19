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
    object["size"] = static_cast<int>(clients.size());
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

    size_t nbr_clients = 0;
    if(object.contains("size") && object["size"].isDouble())
    {
        nbr_clients = object["size"].isDouble();
    }

    for(size_t i = 0; i < nbr_clients; i++)
    {
        client client;
        QString id = QString::number(i);

        if(object.contains(id) && object[id].isObject())
        {
            QJsonObject json = object[id].toObject();
            if(json.contains("name") && json["name"].isString())
            {
                client.name = json["name"].isString();
            }

            if(json.contains("surname") && json["surname"].isString())
            {
                client.surname = json["surname"].isString();
            }

            if(json.contains("address") && json["address"].isString())
            {
                client.address = json["address"].isString();
            }

            if(json.contains("zip") && json["zip"].isString())
            {
                client.zip = json["zip"].isString();
            }

            if(json.contains("city") && json["city"].isString())
            {
                client.city = json["city"].isString();
            }

            if(json.contains("phone") && json["phone"].isString())
            {
                client.phone = json["phone"].isString();
            }

            if(json.contains("email") && json["email"].isString())
            {
                client.email = json["email"].isString();
            }
        }

        clients.push_back(client);
    }

    file.close();
}

#include "dbhandler.h"

DBHandler::DBHandler()
{

}

DBHandler::~DBHandler()
{

}

void DBHandler::loadAll(std::vector<DrawerData>& datas)
{
    QFile file(FILE_NAME);
    if(!file.open(QIODevice::ReadWrite))
    {
        qWarning("Failed to open the file for reading !");
    }

    QByteArray raw_data = file.readAll();
    QJsonDocument document = QJsonDocument::fromJson(raw_data);
    QJsonObject object = document.object();

    for(int i = 0; i < 41; i++)
    {
        DrawerData data;
        QString id = QString::number(i);

        if(object.contains(id) && object[id].isObject())
        {
            QJsonObject json = object[id].toObject();
            if(json.contains("status") && json["status"].isDouble())
            {
                data.setStatus(json["status"].toInt());
            }

            if(json.contains("name") && json["name"].isString())
            {
                data.setName(json["name"].toString());
            }

            if(json.contains("surname") && json["surname"].isString())
            {
                data.setSurname(json["surname"].toString());
            }
        }

        datas.push_back(data);
    }

    file.close();
}

void DBHandler::saveAll(std::vector<DrawerData>& datas)
{
    QFile file(FILE_NAME);
    if(!file.open(QIODevice::ReadWrite))
    {
        qWarning("Failed to open the file for reading !");
    }

    QJsonObject object;
    for(uint i = 0; i < datas.size(); i++)
    {
        QString id = QString::number(i);
        QJsonObject json;
        json["status"] = datas[i].getStatus();
        json["name"] = datas[i].getName();
        json["surname"] = datas[i].getSurname();

        object[id] = json;
    }

    QJsonDocument document(object);
    file.write(document.toJson());

    file.close();
}

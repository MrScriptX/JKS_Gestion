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

            if(json.contains("contact") && json["contact"].isString())
            {
                data.setContact(json["contact"].toString());
            }

            if(json.contains("deposit date") && json["deposit date"].isString())
            {
                data.setDeposit_date(json["deposit date"].toString());
            }

            if(json.contains("breakdown") && json["breakdown"].isString())
            {
                data.setBreakdown(json["breakdown"].toString());
            }

            if(json.contains("complementary info") && json["complementary info"].isString())
            {
                data.setComplementary_info(json["complementary info"].toString());
            }

            if(json.contains("repairs") && json["repairs"].isString())
            {
                data.setRepairs(json["repairs"].toString());
            }

            if(json.contains("comments") && json["comments"].isString())
            {
                data.setComments(json["comments"].toString());
            }

            if(json.contains("price") && json["price"].isString())
            {
                data.setPrice(json["price"].toString());
            }

            if(json.contains("client awarness") && json["client awarness"].isDouble())
            {
                data.setClient_awarness(json["client awarness"].toInt());
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
        json["contact"] = datas[i].getContact();
        json["deposit date"] = datas[i].getDeposit_date();
        json["breakdown"] = datas[i].getBreakdown();
        json["complementary info"] = datas[i].getComplementary_info();
        json["repairs"] = datas[i].getRepairs();
        json["comments"] = datas[i].getComments();
        json["price"] = datas[i].getPrice();
        json["client awarness"] = datas[i].getClient_awarness();

        object[id] = json;
    }

    QJsonDocument document(object);
    file.write(document.toJson());

    file.close();
}

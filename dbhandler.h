#ifndef DBHANDLER_H
#define DBHANDLER_H

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <memory>
#include <iostream>

#include "contactdata.h"
#include "drawerdata.h"

class DBHandler
{
public:
    DBHandler();
    ~DBHandler();

    QJsonObject& getJsonObject();
    QJsonDocument& getJsonDocument();
    QFile& getFile();

    void loadAll(std::vector<DrawerData>& datas);
    void saveAll(std::vector<DrawerData>& datas);

    void loadContactData(const QString& file_name, ContactData* data);
    void saveContactData(const QString& file_name, ContactData* data);

    void deleteFileData(const QString& file_name);
private:

    const QString FILE_NAME = "data.json";
};

#endif // DBHANDLER_H

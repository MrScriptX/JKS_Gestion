#ifndef DBHANDLER_H
#define DBHANDLER_H

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

#include <memory>
#include <iostream>

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

private:

    const QString FILE_NAME = "data.json";
};

#endif // DBHANDLER_H

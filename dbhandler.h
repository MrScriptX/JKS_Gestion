#ifndef DBHANDLER_H
#define DBHANDLER_H

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

#include <memory>

class DBHandler
{
public:
    DBHandler();
    ~DBHandler();

    QJsonObject& getJsonObject();
    QJsonDocument& getJsonDocument();
    QFile& getFile();
private:
    QFile m_file;
    QJsonDocument m_document;
    QJsonObject m_object;
};

#endif // DBHANDLER_H

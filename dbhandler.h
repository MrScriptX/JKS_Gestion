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

private:
    std::unique_ptr<QFile> m_pFile;
    std::unique_ptr<QJsonDocument> m_pDocument;
    std::unique_ptr<QJsonObject> m_pObject;
};

#endif // DBHANDLER_H

#include "dbhandler.h"

DBHandler::DBHandler()
{
    m_pFile = std::make_unique<QFile>("data.json");
    if(!m_pFile->open(QIODevice::ReadWrite))
    {
        qWarning("Failed to open data.json !");
    }

    QByteArray raw_data = m_pFile->readAll();

    m_pDocument = std::make_unique<QJsonDocument>(QJsonDocument::fromJson(raw_data));
    m_pObject = m_pDocument->object();
}

QJsonObject& DBHandler::getJsonObject()
{
    return m_pObject;
}

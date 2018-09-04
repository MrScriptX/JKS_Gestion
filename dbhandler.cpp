#include "dbhandler.h"

DBHandler::DBHandler()
{
    m_pFile = std::make_unique<QFile>("data.json");
    if(!m_pFile->open(QIODevice::ReadWrite))
    {
        qWarning("Failed to open data.json !");
    }

    QByteArray raw_data = m_pFile->readAll();

    m_document = QJsonDocument::fromJson(raw_data);
    m_object = m_document.object();
}

DBHandler::~DBHandler()
{
    m_pFile->close();
}

QJsonObject& DBHandler::getJsonObject()
{
    return m_object;
}

QJsonDocument& DBHandler::getJsonDocument()
{
    return m_document;
}

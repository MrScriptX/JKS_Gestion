#include "dbhandler.h"

DBHandler::DBHandler()
{
    m_file.setFileName("data.json");
    if(!m_file.open(QIODevice::ReadWrite))
    {
        qWarning("Failed to open data.json !");
    }

    QByteArray raw_data = m_file.readAll();

    m_document = QJsonDocument::fromJson(raw_data);
    m_object = m_document.object();
}

DBHandler::~DBHandler()
{
    m_file.close();
}

QJsonObject& DBHandler::getJsonObject()
{
    return m_object;
}

QJsonDocument& DBHandler::getJsonDocument()
{
    return m_document;
}

QFile& DBHandler::getFile()
{
    return m_file;
}

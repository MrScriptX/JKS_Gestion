#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("JKS Gestion");
    setMinimumWidth(800);
    setMinimumHeight(800);

    setupWindow();
}

void MainWindow::setupWindow()
{
    for(uint32_t i = 0; i < 41; i++)
    {
        QString name;
        QString surname;
        Status status = Status::EMPTY;

        QString file_name = QString::number(static_cast<int>(i)) + ".json";
        QFile file(file_name);
        if(!file.open(QIODevice::ReadOnly))
        {
            qWarning("Failed to open file for data reading : MainWindow::openDrawer");
        }
        QByteArray raw_data = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(raw_data);
        QJsonObject doc_object = doc.object();

        QJsonObject json = doc_object[QString::number(i)].toObject();
        if(json.contains("name") && json["name"].isString())
        {
            name = json["name"].toString();
        }

        if(json.contains("surname") && json["surname"].isString())
        {
            surname = json["surname"].toString();
        }

        if(json.contains("status") && json["status"].isDouble())
        {
            status = static_cast<Status>(json["status"].toInt());
        }


        QString client;
        //temp
        if(name == "" || surname == "")
        {
           client = "empty";
           status = Status::EMPTY;
        }
        else
        {
            client = name + " " + surname;
        }
        //end temp

        QPushButton* drawer = new QPushButton;
        drawer->setText(QString::number(i) + " : " + client);
        if(status != Status::EMPTY)
        {
            if(status != Status::READY)
            {
                drawer->setStyleSheet("background-color: orange;");
            }
            else
            {
                drawer->setStyleSheet("background-color: green;");
            }
        }


        m_drawers.push_back(drawer);
        connect(m_drawers[i], &QPushButton::clicked, this, [&, i]() { openDrawer(i); });

        file.close();
    }

    QGridLayout* layout = new QGridLayout;
    for(uint32_t i = 0; i < m_drawers.size(); i++)
    {
        if(i + 1 < 11)
        {
            layout->addWidget(m_drawers.at(i + 1), static_cast<int>(i + 1), 1);
        }
        else if(i < 21)
        {
            layout->addWidget(m_drawers.at(i), static_cast<int>(i - 10), 2);
        }
        else if(i < 31)
        {
            layout->addWidget(m_drawers.at(i), static_cast<int>(i - 20), 3);
        }
        else
        {
            layout->addWidget(m_drawers.at(i), static_cast<int>(i - 30), 4);
        }
    }

    QWidget* centralWidget = new QWidget;
    centralWidget->setLayout(layout);

    setCentralWidget(centralWidget);
}

void MainWindow::openDrawer(uint32_t i)
{
    if(m_drawer != nullptr)
    {
        m_drawer->close();
        m_drawer.reset();
    }

    QString file_name = QString::number(static_cast<int>(i)) + ".json";
    QFile file(file_name);
    if(!file.open(QIODevice::ReadOnly))
    {
        qWarning("Failed to open file for data reading : MainWindow::openDrawer");
    }
    QByteArray raw_data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(raw_data);
    QJsonObject doc_object = doc.object();

    m_drawer = std::make_unique<Drawer>(nullptr);
    m_drawer->loadData(doc_object[QString::number(i)].toObject());
    m_drawer->setID(static_cast<int>(i));
    m_drawer->show();

    connect(m_drawer.get(), SIGNAL(updated()), this, SLOT(updateMain()));

    file.close();
}

void MainWindow::updateMain()
{
    m_drawers.clear();
    setupWindow();
    update();
}

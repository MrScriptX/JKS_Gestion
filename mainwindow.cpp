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
    m_reset = new QAction;
    m_reset->setText("reset");

    if(!m_drawers_data.empty())
    {
        m_drawers_data.clear();
    }

    handler.loadAll(m_drawers_data);

    for(uint32_t i = 0; i < 41; i++)
    {
        QString name;
        QString surname;
        Status status = Status::EMPTY;

        name = m_drawers_data[i].getName();
        surname = m_drawers_data[i].getSurname();
        status = static_cast<Status>(m_drawers_data[i].getStatus());


        QString client;
        //temp
        if(name == "" || name == " ")
        {
           client = "empty";
           status = Status::EMPTY;
        }
        else
        {
            client = surname + " " + name;
        }
        //end temp

        QPushButton* drawer = new QPushButton;
        QFont button_font = drawer->font();
        button_font.setPointSize(10);

        drawer->setFont(button_font);
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
    }

    QGridLayout* layout = new QGridLayout;
    for(uint32_t i = 1; i < m_drawers.size(); i++)
    {
        if(i < 11)
        {
            layout->addWidget(m_drawers.at(i), static_cast<int>(i), 1);
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

    m_drawer = std::make_unique<Drawer>(nullptr);
    m_drawer->setup(static_cast<int>(i), m_drawers_data[i]);
    m_drawer->loadData(m_drawers_data[i]);
    m_drawer->show();

    connect(m_drawer.get(), SIGNAL(updated()), this, SLOT(updateMain()));
}

void MainWindow::updateMain()
{
    handler.saveAll(m_drawers_data);
    m_drawers.clear();
    setupWindow();
    update();
}

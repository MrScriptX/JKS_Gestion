#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("JKS Gestion");
    setMinimumWidth(800);
    setMinimumHeight(800);

    createAction();
    setupWindow();
}

void MainWindow::setupWindow()
{
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
        drawer->setFixedHeight(50);
        if(status != Status::EMPTY)
        {
            if(status != Status::READY)
            {
                drawer->setStyleSheet("QPushButton{ background-color: #ff8300;} "
                                      "QPushButton:hover { background-color: #ffa240;}");
            }
            else
            {
                drawer->setStyleSheet("QPushButton{ background-color: #27b600;} "
                                      "QPushButton:hover { background-color: #5dc840;}");
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

void MainWindow::createAction()
{
    m_client_menu = menuBar()->addMenu(tr("Client"));

    m_receipt = menuBar()->addAction(tr("Receipt"));
    m_receipt->setToolTip(tr("Nouveau recepisse client"));
    connect(m_receipt, &QAction::triggered, this, &MainWindow::receipt);

    m_clientView = m_client_menu->addAction(tr("Voir clients"));
    m_clientView->setToolTip(tr("Visualiser la liste des clients enregistrés"));
    connect(m_clientView, &QAction::triggered, this, &MainWindow::clientViewer);

    m_add_client = m_client_menu->addAction(tr("Ajouter client"));
    m_add_client->setToolTip(tr("Ajouter de nouveaux client à la base de données"));
    connect(m_add_client, &QAction::triggered, this, &MainWindow::addClient);
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

void MainWindow::receipt()
{
    m_receipt_manager.reset();
    m_receipt_manager = std::make_unique<ReceiptManager>();
    m_receipt_manager->show();
}

void MainWindow::clientViewer()
{
    m_cManager.reset();
    m_cManager = std::make_unique<ClientManager>();
    m_cManager->tableViewer();
}

void MainWindow::addClient()
{
    m_cManager.reset();
    m_cManager = std::make_unique<ClientManager>();

    QWidget* window = new QWidget;

    QLineEdit* surname = new QLineEdit;
    surname->setPlaceholderText(tr("Prénom"));
    QLineEdit* name = new QLineEdit;
    name->setPlaceholderText(tr("Nom"));
    QLineEdit* address = new QLineEdit;
    address->setPlaceholderText(tr("Address"));
    QLineEdit* zip = new QLineEdit;
    zip->setPlaceholderText(tr("Code Postal"));
    QLineEdit* city = new QLineEdit;
    city->setPlaceholderText(tr("Ville"));
    QLineEdit* phone = new QLineEdit;
    phone->setPlaceholderText(tr("Téléphone"));
    QLineEdit* email = new QLineEdit;
    email->setPlaceholderText(tr("Courriel"));

    QPushButton* validate = new QPushButton;
    validate->setText(tr("Validez"));
    connect(validate, &QPushButton::clicked, this, [this, window, surname, name, address, zip, city, phone, email]{
        switch( QMessageBox::question(window, tr("Attention"),
                    tr("Voulez-vous vraiment AJOUTER ce nouveau clients ?"),
                    QMessageBox::Yes | QMessageBox::No, QMessageBox::No))
        {
          case QMessageBox::Yes:
            break;
          case QMessageBox::No:
            return;
          default:
            return;
        }

        client client;
        client.surname = surname->text();
        client.name = name->text();
        client.address = address->text();
        client.zip = zip->text();
        client.city = city->text();
        client.phone = phone->text();
        client.email = email->text();

        m_cManager->saveClient(client);
        window->close();
    });

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(surname);
    layout->addWidget(name);
    layout->addWidget(address);
    layout->addWidget(zip);
    layout->addWidget(city);
    layout->addWidget(phone);
    layout->addWidget(email);
    layout->addWidget(validate);

    window->setLayout(layout);
    window->show();
}

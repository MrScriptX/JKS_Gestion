#include "receiptmanager.h"

ReceiptManager::ReceiptManager(QWidget *parent) : QWidget(parent)
{
    m_tmpClient = std::make_shared<client>();

    buildHeaderBox();

    title = new QLabel("PRISE EN CHARGE DU MATERIEL EN SERVICE APRES VENTE");
    {
        QFont f = title->font();
        f.setPointSize(10);
        title->setFont(f);
    }
    title->setContentsMargins(80, 0, 0, 0);
    buildClientBox();

    subtitle = new QLabel("Identification du Matériel et panne constatée");
    {
        QFont f = subtitle->font();
        f.setPointSize(10);
        subtitle->setFont(f);
    }
    subtitle->setContentsMargins(20, 0, 0, 0);
    buildDepositBox();

    receipt_title = new QLabel("--------------------------------------------------");
    receipt_title->setAlignment(Qt::AlignHCenter);
    receipt_title->setContentsMargins(0, 20, 0, 20);
    buildClientReceiptBox();

    footer = new QLabel("Un devis sera proposé pour toute réparation supérieure à 50% de la valeur neuve de l'appareil ou à "
                        "partir de 150€ TTC.\nLes devis sont payants, la somme demandée en acompte couvre les frais de démontage,"
                        "de diagnostic de panne, etc... "
                        "Les frais de devis seront à\ndéduire sur acceptation de celui-ci. Tout devis n'est valable qu'un mois et les "
                        "tarifs peuvent êtres modifiées à tous moments.\n"
                        "Tout refus de devis avec récupération du matériel sera facturé 23€ TTC.");
    {
        QFont f = footer->font();
        f.setPointSize(6);
        footer->setFont(f);
    }

    m_print = new QPushButton;
    m_print->setText(tr("Imprimer"));
    m_print->setToolTip(tr("Imprimer la page"));
    connect(m_print, SIGNAL(clicked()), this, SLOT(print()));

    QVBoxLayout* container = new QVBoxLayout;
    container->addLayout(header);
    container->addSpacing(10);
    container->addWidget(title);
    container->addWidget(client_box);
    container->addSpacing(10);
    container->addWidget(subtitle);
    container->addWidget(deposit_box);
    container->addWidget(receipt_title);
    container->addWidget(receipt_box);
    container->addWidget(footer);
    container->addWidget(m_print);

    QFile file(":/stylesheets/printstyle.qss");
    file.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(file.readAll());
    file.close();

    setStyleSheet(StyleSheet);
    setFixedSize(673, 950);
    setLayout(container);
}

void ReceiptManager::buildHeaderBox()
{
    QLabel* address_jks = new QLabel("STE JKS-informatique - 10 RUE DU Maréchal FOCH - 67380 LINGOLSHEIM");
    QLabel* email_jks = new QLabel("Courriel: info@jks-informatique.com             Tel: 03.69.81.82.11");

    header = new QVBoxLayout;
    header->addWidget(address_jks);
    header->addSpacing(2);
    header->addWidget(email_jks);
    header->setContentsMargins(100, 0, 20, 0);
}

void ReceiptManager::buildClientBox()
{
    datel = new QLabel(tr("Date : "));
    date = new QLineEdit;
    QHBoxLayout* date_lt = new QHBoxLayout;
    date_lt->addWidget(datel);
    date_lt->addWidget(date);

    namel = new QLabel(tr("Nom : "));
    name = new QLineEdit;
    surnamel = new QLabel(tr("Prénom : "));
    surname = new QLineEdit;
    QHBoxLayout* name_lt = new QHBoxLayout;
    name_lt->addWidget(namel);
    name_lt->addWidget(name);
    name_lt->addWidget(surnamel);
    name_lt->addWidget(surname);

    addressl = new QLabel(tr("Adresse : "));
    address = new QLineEdit;
    QHBoxLayout* address_lt = new QHBoxLayout;
    address_lt->addWidget(addressl);
    address_lt->addWidget(address);

    postal_codel = new QLabel(tr("Code Postal : "));
    postal_code = new QLineEdit;
    cityl = new QLabel(tr("Ville : "));
    city = new QLineEdit;
    QHBoxLayout* city_lt = new QHBoxLayout;
    city_lt->addWidget(postal_codel);
    city_lt->addWidget(postal_code);
    city_lt->addWidget(cityl);
    city_lt->addWidget(city);

    phonel = new QLabel(tr("Téléphone : "));
    phone = new QLineEdit;
    emaill = new QLabel(tr("Courriel : "));
    email = new QLineEdit;
    QHBoxLayout* contact_lt = new QHBoxLayout;
    contact_lt->addWidget(phonel);
    contact_lt->addWidget(phone);
    contact_lt->addWidget(emaill);
    contact_lt->addWidget(email);

    m_client = new QPushButton;
    m_client->setText("Add client");
    connect(m_client, &QPushButton::clicked, this, &ReceiptManager::fillClient);

    m_save_client = new QPushButton;
    m_save_client->setText(tr("Save client"));
    connect(m_save_client, &QPushButton::clicked, this, &ReceiptManager::saveClient);

    QHBoxLayout* button_container = new QHBoxLayout;
    button_container->addWidget(m_client);
    button_container->addWidget(m_save_client);

    QVBoxLayout* container = new QVBoxLayout;
    container->addLayout(date_lt);
    container->addLayout(name_lt);
    container->addLayout(address_lt);
    container->addLayout(city_lt);
    container->addLayout(contact_lt);
    container->addLayout(button_container);

    client_box = new QGroupBox;
    client_box->setTitle("Information Client");
    client_box->setLayout(container);
}

void ReceiptManager::buildDepositBox()
{
    mat_typel = new QLabel(tr("Type Matériel : "));
    mat_type = new QLineEdit;
    QHBoxLayout* mat_type_lt = new QHBoxLayout;
    mat_type_lt->addWidget(mat_typel);
    mat_type_lt->addWidget(mat_type);

    passwordl = new QLabel(tr("Mot de passe : "));
    password = new QLineEdit;
    savel = new QLabel(tr("Sauvergardes : "));
    save = new QLineEdit;
    chargerl = new QLabel(tr("Chargeur : "));
    charger = new QLineEdit;
    QHBoxLayout* info = new QHBoxLayout;
    info->addWidget(passwordl);
    info->addWidget(password);
    info->addWidget(savel);
    info->addWidget(save);
    info->addWidget(chargerl);
    info->addWidget(charger);

    statel = new QLabel(tr("Etat Physique : "));
    state = new QTextEdit;
    QVBoxLayout* state_lt = new QVBoxLayout;
    state_lt->addWidget(statel);
    state_lt->addWidget(state);

    breakdownl = new QLabel(tr("Panne constatée : "));
    breakdown = new QTextEdit;
    QVBoxLayout* breakdown_lt = new QVBoxLayout;
    breakdown_lt->addWidget(breakdownl);
    breakdown_lt->addWidget(breakdown);

    operationl = new QLabel(tr("Réparation effectué"));
    operation = new QTextEdit;
    QVBoxLayout* operation_lt = new QVBoxLayout;
    operation_lt->addWidget(operationl);
    operation_lt->addWidget(operation);

    QVBoxLayout* container = new QVBoxLayout;
    container->addLayout(mat_type_lt);
    container->addLayout(info);
    container->addLayout(state_lt);
    container->addLayout(breakdown_lt);
    container->addLayout(operation_lt);

    deposit_box = new QGroupBox;
    deposit_box->setTitle("Information Dépot");
    deposit_box->setLayout(container);
}

void ReceiptManager::buildClientReceiptBox()
{
    date_depl = new QLabel(tr("Date de dépot : "));
    date_dep = new QLineEdit;
    QHBoxLayout* date_lt = new QHBoxLayout;
    date_lt->addWidget(date_depl);
    date_lt->addWidget(date_dep);

    name_surl = new QLabel(tr("Nom et prénom : "));
    name_sur = new QLineEdit;
    QHBoxLayout* name_lt = new QHBoxLayout;
    name_lt->addWidget(name_surl);
    name_lt->addWidget(name_sur);

    mat_type_bisl = new QLabel(tr("Type matériel : "));
    mat_type_bis = new QLineEdit;
    brandl = new QLabel(tr("Marque/modele : "));
    brand = new QLineEdit;
    QHBoxLayout* computer_lt = new QHBoxLayout;
    computer_lt->addWidget(mat_type_bisl);
    computer_lt->addWidget(mat_type_bis);
    computer_lt->addStretch();
    computer_lt->addWidget(brandl);
    computer_lt->addWidget(brand);

    QVBoxLayout* container = new QVBoxLayout;
    container->addLayout(date_lt);
    container->addLayout(name_lt);
    container->addLayout(computer_lt);

    receipt_box = new QGroupBox;
    receipt_box->setTitle("Recepisse Client");
    receipt_box->setLayout(container);
}

void ReceiptManager::print()
{
    m_print->setVisible(false);
    m_client->setVisible(false);
    m_save_client->setVisible(false);

    QPrinter printer;

    QPrintDialog dialog(&printer, this);
    dialog.setWindowTitle(tr("Imprimer"));

    if (dialog.exec() != QDialog::Accepted)
    {
        m_print->setVisible(true);
        m_client->setVisible(true);
        m_save_client->setVisible(true);
        return;
    }

    QPainter painter;
    painter.begin(&printer);
    this->render(&painter);

    painter.end();

    m_print->setVisible(true);
    m_client->setVisible(true);
    m_save_client->setVisible(true);
}

void ReceiptManager::fillClient()
{
    m_cManager.reset();
    m_cManager = std::make_unique<ClientManager>();
    m_cManager->viewer(Client::FETCH_CLIENT, m_tmpClient);

    connect(m_cManager.get(), SIGNAL(clientSelected()), this, SLOT(updateClient()));
}

void ReceiptManager::updateClient()
{
    name->setText(m_tmpClient->name);
    surname->setText(m_tmpClient->surname);
    address->setText(m_tmpClient->address);
    postal_code->setText(m_tmpClient->zip);
    city->setText(m_tmpClient->city);
    phone->setText(m_tmpClient->phone);
    email->setText(m_tmpClient->email);
}

void ReceiptManager::saveClient()
{
    client c;
    c.name = name->text();
    c.surname = surname->text();
    c.address = address->text();
    c.zip = postal_code->text();
    c.city = city->text();
    c.phone = phone->text();
    c.email = email->text();

    m_cManager.reset();
    m_cManager = std::make_unique<ClientManager>();
    m_cManager->saveClient(c);
}

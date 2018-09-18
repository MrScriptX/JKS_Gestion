#include "receiptmanager.h"

ReceiptManager::ReceiptManager(QWidget *parent) : QWidget(parent)
{
    title = new QLabel("PRISE EN CHARGE DU MATERIEL EN SERVICE APRES VENTE")
}

void ReceiptManager::buildClientBox()
{
    datel = new QLabel(tr("Date : "));
    date = new QLineEdit;
    QVBoxLayout* date_lt = new QVBoxLayout;
    date_lt->addWidget(datel);
    date_lt->addWidget(date);

    namel = new QLabel(tr("Nom : "));
    name = new QLineEdit;
    surnamel = new QLabel(tr("Prénom : "));
    surname = new QLineEdit;
    QVBoxLayout* name_lt = new QVBoxLayout;
    name_lt->addWidget(namel);
    name_lt->addWidget(name);
    name_lt->addStretch();
    name_lt->addWidget(surnamel);
    name_lt->addWidget(surname);

    addressl = new QLabel(tr("Adresse : "));
    address = new QLineEdit;
    QVBoxLayout* address_lt = new QVBoxLayout;
    address_lt->addWidget(addressl);
    address_lt->addWidget(address);

    postal_codel = new QLabel(tr("Code Postal : "));
    postal_code = new QLineEdit;
    cityl = new QLabel(tr("Ville : "));
    city = new QLineEdit;
    QVBoxLayout* city_lt = new QVBoxLayout;
    city_lt->addWidget(postal_codel);
    city_lt->addWidget(postal_code);
    city_lt->addStretch();
    city_lt->addWidget(cityl);
    city_lt->addWidget(city);

    phonel = new QLabel(tr("Téléphone : "));
    phone = new QLineEdit;
    emaill = new QLabel(tr("Courriel : "));
    email = new QLineEdit;
    QVBoxLayout* contact_lt = new QVBoxLayout;
    contact_lt->addWidget(addressl);
    contact_lt->addWidget(address);
    contact_lt->addStretch();
    contact_lt->addWidget(emaill);
    contact_lt->addWidget(email);

    QHBoxLayout* container = new QHBoxLayout;
    container->addLayout(date_lt);
    container->addLayout(name_lt);
    container->addLayout(address_lt);
    container->addLayout(city_lt);
    container->addLayout(contact_lt);

    client_box = new QGroupBox;
    client_box->setTitle("Information Client");
    client_box->setLayout(container);
}

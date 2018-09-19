#include "receiptmanager.h"

ReceiptManager::ReceiptManager(QWidget *parent) : QWidget(parent)
{
    title = new QLabel("PRISE EN CHARGE DU MATERIEL EN SERVICE APRES VENTE");
    buildClientBox();

    subtitle = new QLabel("Identification du Matériel et panne constatée");
    buildDepositBox();

    receipt_title = new QLabel("--------------------------------------------------");
    receipt_title->setAlignment(Qt::AlignHCenter);
    receipt_title->setContentsMargins(0, 20, 0, 20);
    buildClientReceiptBox();

    m_print = new QPushButton;
    m_print->setText(tr("Imprimer"));
    m_print->setToolTip(tr("Imprimer la page"));
    connect(m_print, SIGNAL(clicked()), this, SLOT(print()));

    QVBoxLayout* container = new QVBoxLayout;
    container->addWidget(title);
    container->addWidget(client_box);
    container->addWidget(subtitle);
    container->addWidget(deposit_box);
    container->addWidget(receipt_title);
    container->addWidget(receipt_box);
    container->addWidget(m_print);

    QFile file(":/stylesheets/printstyle.qss");
    file.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(file.readAll());
    file.close();

    setStyleSheet(StyleSheet);
    setFixedSize(673, 950);
    setLayout(container);
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

    QVBoxLayout* container = new QVBoxLayout;
    container->addLayout(date_lt);
    container->addLayout(name_lt);
    container->addLayout(address_lt);
    container->addLayout(city_lt);
    container->addLayout(contact_lt);

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
    QPrinter printer;

    QPrintDialog dialog(&printer, this);
    dialog.setWindowTitle(tr("Imprimer"));

    if (dialog.exec() != QDialog::Accepted)
    {
        return;
    }

    QPainter painter;
    painter.begin(&printer);
    this->render(&painter);

    painter.end();
}

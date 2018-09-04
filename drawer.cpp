#include "drawer.h"

Drawer::Drawer(QWidget *parent) : QWidget(parent)
{
    client_aware = true;

    setWindowTitle("Case");
    setMinimumHeight(600);
    setMinimumWidth(1000);

    status = new QComboBox;
    status->addItem("VIDE");
    status->addItem("EN ATTENTE DE REPERATION");
    status->addItem("EN ATTENTE DE PIECE");
    status->addItem("EN ATTENTE D'ACCORD CLIENT");
    status->addItem("REPARE");
    status->setCurrentIndex(static_cast<int>(Status::EMPTY));
    status->setEnabled(false);

    client_awarness = new QLabel;
    QPixmap awarness_ico = QPixmap::fromImage(QImage(":/image/check_ico.png"));
    client_awarness->setPixmap(awarness_ico);
    client_awarness->setFixedSize(32, 32);
    client_awarness->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
    client_awarness->setScaledContents(true);
    QLabel* l_awarness = new QLabel;
    l_awarness->setText("Client prévenu : ");

    client_awarness_edit = new QComboBox;
    client_awarness_edit->addItem("OUI");
    client_awarness_edit->addItem("NON");
    client_awarness_edit->setVisible(false);

    QHBoxLayout* client_awarness_layout = new QHBoxLayout;
    client_awarness_layout->addWidget(l_awarness);
    client_awarness_layout->addWidget(client_awarness_edit);
    client_awarness_layout->addWidget(client_awarness);

    QVBoxLayout* status_layout = new QVBoxLayout;
    status_layout->addWidget(status);
    status_layout->addLayout(client_awarness_layout);

    QGroupBox* status_box = new QGroupBox;
    status_box->setTitle("Status");
    status_box->setLayout(status_layout);



    name = new QLineEdit;
    name->setMaximumWidth(300);
    name->setFrame(false);
    name->setReadOnly(true);
    name->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");
    QLabel* l_name = new QLabel("Nom : ");

    surname = new QLineEdit;
    surname->setMaximumWidth(300);
    surname->setFrame(false);
    surname->setReadOnly(true);
    surname->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");
    QLabel* l_surname = new QLabel("Prenom : ");

    contact = new QLineEdit;
    contact->setMaximumWidth(300);
    contact->setFrame(false);
    contact->setReadOnly(true);
    contact->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");
    QLabel* l_contact = new QLabel("Contact : ");


    deposit_date = new QLineEdit;
    deposit_date->setMaximumWidth(200);
    deposit_date->setFrame(false);
    deposit_date->setReadOnly(true);
    deposit_date->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");
    QLabel* l_deposit_date = new QLabel("Date de dépot : ");

    breakdown = new QTextEdit;
    breakdown->setReadOnly(true);
    breakdown->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");
    QHBoxLayout* breakdown_layout = new QHBoxLayout;
    breakdown_layout->addWidget(breakdown);
    QGroupBox* l_breakdown = new QGroupBox;
    l_breakdown->setTitle("Panne constatée");
    l_breakdown->setLayout(breakdown_layout);


    complement_info = new QTextEdit;
    complement_info->setReadOnly(true);
    complement_info->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");
    QHBoxLayout* complement_info_layout = new QHBoxLayout;
    complement_info_layout->addWidget(complement_info);
    QGroupBox* l_complement_info = new QGroupBox;
    l_complement_info->setTitle("Info complementaire");
    l_complement_info->setLayout(complement_info_layout);


    repair = new QTextEdit;
    repair->setReadOnly(true);
    repair->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");
    QHBoxLayout* repair_layout = new QHBoxLayout;
    repair_layout->addWidget(repair);
    QGroupBox* l_repair = new QGroupBox;
    l_repair->setTitle("Réparations opérées");
    l_repair->setLayout(repair_layout);

    comments = new QTextEdit;
    comments->setReadOnly(true);
    comments->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");
    QHBoxLayout* comments_layout = new QHBoxLayout;
    comments_layout->addWidget(comments);
    QGroupBox* l_comments = new QGroupBox;
    l_comments->setTitle("Commentaire");
    l_comments->setLayout(comments_layout);

    price = new QLineEdit;
    price->setMaximumWidth(200);
    price->setFrame(false);
    price->setReadOnly(true);
    price->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");
    QLabel* l_price = new QLabel("Prix : ");


    modify = new QPushButton;
    modify->setText("Editer");
    modify->setDisabled(false);
    connect(modify, SIGNAL(clicked()), this, SLOT(setEditable()));

    save = new QPushButton;
    save->setText("Sauvegarder");
    save->setDisabled(true);
    connect(save, SIGNAL(clicked()), this, SLOT(saveChange()));

    discard = new QPushButton;
    discard->setText("Annuler");
    discard->setDisabled(true);
    connect(discard, SIGNAL(clicked()), this, SLOT(discardChange()));

    QVBoxLayout* action_layout = new QVBoxLayout;
    action_layout->addWidget(modify);
    action_layout->addWidget(save);
    action_layout->addWidget(discard);



    QHBoxLayout* name_layout = new QHBoxLayout;
    name_layout->addWidget(l_name);
    name_layout->addWidget(name);
    name_layout->addStretch();

    QHBoxLayout* surname_layout = new QHBoxLayout;
    surname_layout->addWidget(l_surname);
    surname_layout->addWidget(surname);
    surname_layout->addStretch();

    QHBoxLayout* contact_layout = new QHBoxLayout;
    contact_layout->addWidget(l_contact);
    contact_layout->addWidget(contact);
    contact_layout->addStretch();

    QHBoxLayout* deposit_layout = new QHBoxLayout;
    deposit_layout->addWidget(l_deposit_date);
    deposit_layout->addWidget(deposit_date);
    deposit_layout->addStretch();

    QVBoxLayout* personal_info = new QVBoxLayout;
    personal_info->addLayout(name_layout);
    personal_info->addLayout(surname_layout);
    personal_info->addLayout(contact_layout);
    personal_info->addLayout(deposit_layout);


    QHBoxLayout* top_part = new QHBoxLayout;
    top_part->addLayout(personal_info);
    top_part->addWidget(status_box);
    top_part->addLayout(action_layout);


    QHBoxLayout* price_layout = new QHBoxLayout;
    price_layout->addWidget(l_price);
    price_layout->addWidget(price);
    price_layout->addStretch();


    QVBoxLayout* window = new QVBoxLayout;
    window->addLayout(top_part);
    window->addWidget(l_breakdown);
    window->addWidget(l_complement_info);
    window->addWidget(l_repair);
    window->addWidget(l_comments);
    window->addLayout(price_layout);

    setLayout(window);
}

void Drawer::setID(const int& id)
{
    m_id = id;
}

void Drawer::loadData(const QJsonObject& json)
{
    if(json.contains("status") && json["status"].isDouble())
    {
        status->setCurrentIndex(json["status"].toInt());
    }

    if(json.contains("name") && json["name"].isString())
    {
        name->setText(json["name"].toString());
    }

    if(json.contains("surname") && json["surname"].isString())
    {
        surname->setText(json["surname"].toString());
    }

    if(json.contains("contact") && json["contact"].isString())
    {
        contact->setText(json["contact"].toString());
    }

    if(json.contains("deposit date") && json["deposit date"].isString())
    {
        deposit_date->setText(json["deposit date"].toString());
    }

    if(json.contains("breakdown") && json["breakdown"].isString())
    {
        breakdown->setText(json["breakdown"].toString());
    }

    if(json.contains("complementary_info") && json["complementary_info"].isString())
    {
        complement_info->setText(json["complementary_info"].toString());
    }

    if(json.contains("repairs") && json["repairs"].isString())
    {
        repair->setText(json["repairs"].toString());
    }

    if(json.contains("comments") && json["comments"].isString())
    {
        comments->setText(json["comments"].toString());
    }

    if(json.contains("price") && json["price"].isString())
    {
        price->setText(json["price"].toString());
    }

    if(json.contains("client aware") && json["client aware"].isDouble())
    {
        if(json["client aware"].toInt() == 0)
        {
            QPixmap image = QPixmap::fromImage(QImage(":/image/check_ico.png"));
            client_awarness->setPixmap(image);
            client_awarness_edit->setCurrentIndex(0);
        }
        else
        {
            QPixmap image = QPixmap::fromImage(QImage(":/image/cross_ico.png"));
            client_awarness->setPixmap(image);
            client_awarness_edit->setCurrentIndex(1);
        }
    }
}

void Drawer::saveChange()
{
    switch( QMessageBox::question(this, tr("Attention"),
                tr("Voulez-vous vraiment SAUVEGARDER vos changements ?"),
                QMessageBox::Yes | QMessageBox::No, QMessageBox::No))
    {
      case QMessageBox::Yes:
        qWarning("Yes selected !");
        break;
      case QMessageBox::No:
        return;
      default:
        qWarning("Unexpected error occured ! Operation aborted !");
        break;
    }

    QString file_name = QString::number(m_id) + ".json";
    QFile file(file_name);
    if(!file.open(QIODevice::WriteOnly))
    {
        qWarning("Failed to open save.json");
    }

    QJsonObject content;
    content["status"] = status->currentIndex();
    content["client aware"] = client_awarness_edit->currentIndex();
    content["name"] = name->text();
    content["surname"] = surname->text();
    content["contact"] = contact->text();
    content["deposit date"] = deposit_date->text();
    content["breakdown"] = breakdown->toPlainText();
    content["complementary_info"] = complement_info->toPlainText();
    content["repairs"] = repair->toPlainText();
    content["comments"] = comments->toPlainText();
    content["price"] = price->text();

    QJsonObject file_object;
    file_object[QString::number(m_id)] = content;
    loadData(content);

    QJsonDocument doc(file_object);
    file.write(doc.toJson());

    file.close();

    status->setEnabled(false);
    client_awarness->setVisible(true);
    client_awarness_edit->setVisible(false);

    name->setFrame(false);
    name->setReadOnly(true);
    name->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");

    surname->setFrame(false);
    surname->setReadOnly(true);
    surname->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");

    contact->setFrame(false);
    contact->setReadOnly(true);
    contact->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");

    deposit_date->setFrame(false);
    deposit_date->setReadOnly(true);
    deposit_date->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");

    price->setFrame(false);
    price->setReadOnly(true);
    price->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");

    breakdown->setReadOnly(true);
    breakdown->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");

    complement_info->setReadOnly(true);
    complement_info->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");

    repair->setReadOnly(true);
    repair->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");

    comments->setReadOnly(true);
    comments->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");

    modify->setText("Editer");
    modify->setDisabled(false);

    save->setText("Sauvergarder");
    save->setDisabled(true);

    discard->setText("Annuler");
    discard->setDisabled(true);

    update();
    emit updated();
}

void Drawer::discardChange()
{
    switch( QMessageBox::question(this, tr("Attention"),
                tr("Voulez-vous vraiment ANNULER vos changements ?"),
                QMessageBox::Yes | QMessageBox::No, QMessageBox::No))
    {
      case QMessageBox::Yes:
        qWarning("Yes selected !");
        break;
      case QMessageBox::No:
        return;
      default:
        qWarning("Unexpected error occured ! Operation aborted !");
        break;
    }

    QString file_name = QString::number(m_id) + ".json";
    QFile file(file_name);
    if(!file.open(QIODevice::ReadOnly))
    {
        qWarning("Failed to save change!");
    }

    QByteArray file_data = file.readAll();
    QJsonDocument save_file(QJsonDocument::fromJson(file_data));
    QJsonObject file_object = save_file.object();

    loadData(file_object[QString::number(m_id)].toObject());

    file.close();

    status->setEnabled(false);
    client_awarness->setVisible(true);
    client_awarness_edit->setVisible(false);

    name->setFrame(false);
    name->setReadOnly(true);
    name->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");

    surname->setFrame(false);
    surname->setReadOnly(true);
    surname->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");

    contact->setFrame(false);
    contact->setReadOnly(true);
    contact->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");

    deposit_date->setFrame(false);
    deposit_date->setReadOnly(true);
    deposit_date->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");

    price->setFrame(false);
    price->setReadOnly(true);
    price->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");

    breakdown->setReadOnly(true);
    breakdown->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");

    complement_info->setReadOnly(true);
    complement_info->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");

    repair->setReadOnly(true);
    repair->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");

    comments->setReadOnly(true);
    comments->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");

    modify->setText("Editer");
    modify->setDisabled(false);

    save->setText("Sauvergarder");
    save->setDisabled(true);

    discard->setText("Annuler");
    discard->setDisabled(true);

    update();
}

void Drawer::setEditable()
{
    status->setEnabled(true);
    client_awarness->setVisible(false);
    client_awarness_edit->setVisible(true);

    name->setFrame(true);
    name->setReadOnly(false);
    name->setStyleSheet("* { background-color: rgba(255, 255, 255, 1); }");

    surname->setFrame(true);
    surname->setReadOnly(false);
    surname->setStyleSheet("* { background-color: rgba(255, 255, 255, 1); }");

    contact->setFrame(true);
    contact->setReadOnly(false);
    contact->setStyleSheet("* { background-color: rgba(255, 255, 255, 1); }");

    deposit_date->setFrame(true);
    deposit_date->setReadOnly(false);
    deposit_date->setStyleSheet("* { background-color: rgba(255, 255, 255, 1); }");

    price->setFrame(true);
    price->setReadOnly(false);
    price->setStyleSheet("* { background-color: rgba(255, 255, 255, 1); }");

    breakdown->setReadOnly(false);
    breakdown->setStyleSheet("* { background-color: rgba(255, 255, 255, 1); }");

    complement_info->setReadOnly(false);
    complement_info->setStyleSheet("* { background-color: rgba(255, 255, 255, 1); }");

    repair->setReadOnly(false);
    repair->setStyleSheet("* { background-color: rgba(255, 255, 255, 1); }");

    comments->setReadOnly(false);
    comments->setStyleSheet("* { background-color: rgba(255, 255, 255, 1); }");

    modify->setText("Editer");
    modify->setDisabled(true);

    save->setText("Sauvergarder");
    save->setDisabled(false);

    discard->setText("Annuler");
    discard->setDisabled(false);

    update();
}

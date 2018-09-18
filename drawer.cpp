#include "drawer.h"


//while in edit mode: set text color to black or white and adjust background color
//warning box button are too small, adjust their size

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
    status->setFixedHeight(30);
    status->setFixedWidth(230);

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


    called = new QPushButton;
    called->setText("Appel fait");
    called->setFixedHeight(40);
    called->setFixedWidth(120);
    connect(called, SIGNAL(clicked()), this, SLOT(callClient()));

    last_call = new QDateEdit;
    last_call->setReadOnly(true);
    last_call->setFixedHeight(40);
    last_call->setFixedWidth(120);

    view_calls = new QPushButton;
    view_calls->setText("Voir appel");
    view_calls->setFixedHeight(40);
    view_calls->setFixedWidth(120);
    connect(view_calls, SIGNAL(clicked()), this, SLOT(call_viewer()));


    QVBoxLayout* call_layout = new QVBoxLayout;
    call_layout->addWidget(called);
    call_layout->addWidget(last_call);
    call_layout->addWidget(view_calls);

    QGroupBox* call_box = new QGroupBox;
    call_box->setTitle("Rappel client");
    call_box->setLayout(call_layout);



    name = new QLineEdit;
    name->setMaximumWidth(300);
    name->setFrame(false);
    name->setReadOnly(true);
    name->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); border : 0;}");
    QLabel* l_name = new QLabel("Nom : ");

    surname = new QLineEdit;
    surname->setMaximumWidth(300);
    surname->setFrame(false);
    surname->setReadOnly(true);
    surname->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); border : 0;}");
    QLabel* l_surname = new QLabel("Prenom : ");

    contact = new QLineEdit;
    contact->setMaximumWidth(300);
    contact->setFrame(false);
    contact->setReadOnly(true);
    contact->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); border : 0;}");
    QLabel* l_contact = new QLabel("Contact : ");


    deposit_date = new QLineEdit;
    deposit_date->setMaximumWidth(200);
    deposit_date->setFrame(false);
    deposit_date->setReadOnly(true);
    deposit_date->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); border : 0;}");
    QLabel* l_deposit_date = new QLabel("Date de dépot : ");

    breakdown = new QTextEdit;
    breakdown->setReadOnly(true);
    breakdown->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); border : 0;}");
    QHBoxLayout* breakdown_layout = new QHBoxLayout;
    breakdown_layout->addWidget(breakdown);
    QGroupBox* l_breakdown = new QGroupBox;
    l_breakdown->setTitle("Panne constatée");
    l_breakdown->setLayout(breakdown_layout);


    complement_info = new QTextEdit;
    complement_info->setReadOnly(true);
    complement_info->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); border : 0;}");
    QHBoxLayout* complement_info_layout = new QHBoxLayout;
    complement_info_layout->addWidget(complement_info);
    QGroupBox* l_complement_info = new QGroupBox;
    l_complement_info->setTitle("Info complementaire");
    l_complement_info->setLayout(complement_info_layout);


    repair = new QTextEdit;
    repair->setReadOnly(true);
    repair->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); border : 0;}");
    QHBoxLayout* repair_layout = new QHBoxLayout;
    repair_layout->addWidget(repair);
    QGroupBox* l_repair = new QGroupBox;
    l_repair->setTitle("Réparations opérées");
    l_repair->setLayout(repair_layout);

    comments = new QTextEdit;
    comments->setReadOnly(true);
    comments->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); border : 0;}");
    QHBoxLayout* comments_layout = new QHBoxLayout;
    comments_layout->addWidget(comments);
    QGroupBox* l_comments = new QGroupBox;
    l_comments->setTitle("Commentaire");
    l_comments->setLayout(comments_layout);

    price = new QLineEdit;
    price->setMaximumWidth(200);
    price->setFrame(false);
    price->setReadOnly(true);
    price->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); border : 0;}");
    QLabel* l_price = new QLabel("Prix : ");

    QHBoxLayout* price_layout = new QHBoxLayout;
    price_layout->addWidget(l_price);
    price_layout->addWidget(price);
    price_layout->addStretch();

    reset_drawer = new QPushButton;
    reset_drawer->setText("Reset");
    reset_drawer->setFixedHeight(40);
    reset_drawer->setFixedWidth(100);
    connect(reset_drawer, SIGNAL(clicked()), this, SLOT(reset()));

    QHBoxLayout* bottom_part = new QHBoxLayout;
    bottom_part->addLayout(price_layout);
    bottom_part->addWidget(reset_drawer);


    modify = new QPushButton;
    modify->setText("Editer");
    modify->setDisabled(false);
    modify->setFixedHeight(40);
    modify->setFixedWidth(100);
    connect(modify, SIGNAL(clicked()), this, SLOT(setEditable()));

    save = new QPushButton;
    save->setText("Sauvegarder");
    save->setDisabled(true);
    save->setFixedHeight(40);
    save->setFixedWidth(100);
    connect(save, SIGNAL(clicked()), this, SLOT(saveChange()));

    discard = new QPushButton;
    discard->setText("Annuler");
    discard->setDisabled(true);
    discard->setFixedHeight(40);
    discard->setFixedWidth(100);
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
    top_part->addWidget(call_box);
    top_part->addLayout(action_layout);


    QVBoxLayout* window = new QVBoxLayout;
    window->addLayout(top_part);
    window->addWidget(l_breakdown);
    window->addWidget(l_complement_info);
    window->addWidget(l_repair);
    window->addWidget(l_comments);
    window->addLayout(bottom_part);

    setLayout(window);
}

void Drawer::call_viewer()
{
    if(m_viewer != nullptr)
    {
        m_viewer.reset();
    }

    QString tmp = "computer" + QString::number(m_id) + ".json";
    m_viewer = std::make_unique<CallViewer>();
    m_viewer->setup(tmp);
    m_viewer->load(m_call_data);
}

void Drawer::reset()
{
    if(!warning("Voulez-vous vraiment EFFACER les données du casier ?"))
    {
        return;
    }

    status->setCurrentIndex(0);
    client_awarness_edit->setCurrentIndex(0);

    name->setText("");
    surname->setText("");
    contact->setText("");
    deposit_date->setText("");
    breakdown->setText("");
    complement_info->setText("");
    repair->setText("");
    comments->setText("");
    price->setText("");

    m_data->setStatus(status->currentIndex());
    m_data->setClient_awarness(client_awarness_edit->currentIndex());
    m_data->setName(name->text());
    m_data->setSurname(surname->text());
    m_data->setContact(contact->text());
    m_data->setDeposit_date(deposit_date->text());
    m_data->setBreakdown(breakdown->toPlainText());
    m_data->setComplementary_info(complement_info->toPlainText());
    m_data->setRepairs(repair->toPlainText());
    m_data->setComments(comments->toPlainText());
    m_data->setPrice(price->text());

    m_call_data.dates().clear();

    DBHandler handler;
    QString file_name = "data/computer" + QString::number(m_id) + ".json";
    handler.saveContactData(file_name, &m_call_data);

    emit updated();
}

void Drawer::setup(const int& id, DrawerData& data)
{
    m_data = &data;
    m_id = id;
}

void Drawer::loadData(const DrawerData& data)
{
    status->setCurrentIndex(data.getStatus());
    if(data.getClient_awarness() == 0)
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

    name->setText(data.getName());
    surname->setText(data.getSurname());
    contact->setText(data.getContact());
    deposit_date->setText(data.getDeposit_date());
    breakdown->setText(data.getBreakdown());
    complement_info->setText(data.getComplementary_info());
    repair->setText(data.getRepairs());
    comments->setText(data.getComments());
    price->setText(data.getPrice());

    DBHandler handler;
    QString file_name = "data/computer" + QString::number(m_id) + ".json";
    handler.loadContactData(file_name, &m_call_data);

    if(!m_call_data.dates().empty())//check if vector is empty
    {
        last_call->setDate(m_call_data.dates().back());
    }
}

void Drawer::saveChange()
{
    if(!warning("Voulez-vous vraiment SAUVEGARDER vos changements ?"))
    {
        return;
    }

    m_data->setStatus(status->currentIndex());
    m_data->setClient_awarness(client_awarness_edit->currentIndex());
    m_data->setName(name->text());
    m_data->setSurname(surname->text());
    m_data->setContact(contact->text());
    m_data->setDeposit_date(deposit_date->text());
    m_data->setBreakdown(breakdown->toPlainText());
    m_data->setComplementary_info(complement_info->toPlainText());
    m_data->setRepairs(repair->toPlainText());
    m_data->setComments(comments->toPlainText());
    m_data->setPrice(price->text());

    if(client_awarness_edit->currentIndex() == 0)
    {
        QPixmap map = QPixmap::fromImage(QImage(":/image/check_ico.png"));
        client_awarness->setPixmap(map);
    }
    else
    {
        QPixmap map = QPixmap::fromImage(QImage(":/image/cross_ico.png"));
        client_awarness->setPixmap(map);
    }

    setReadMode();
    emit updated();
}

void Drawer::callClient()
{
    if(!warning("Confirmez-vous avoir PASSEZ UN APPEL au client ?"))
    {
        return;
    }

    last_call->setDate(QDate::currentDate());
    m_call_data.dates().push_back(last_call->date());

    DBHandler handler;
    QString file_name = "data/computer" + QString::number(m_id) + ".json";
    handler.saveContactData(file_name, &m_call_data);
}

void Drawer::discardChange()
{
    warning("Voulez-vous vraiment ANNULER vos changements ?");

    loadData(*m_data);
    setReadMode();
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

void Drawer::setReadMode()
{
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

bool Drawer::warning(const char msg[])
{
    switch( QMessageBox::question(this, tr("Attention"),
                tr(msg),
                QMessageBox::Yes | QMessageBox::No, QMessageBox::No))
    {
      case QMessageBox::Yes:
        return true;
      case QMessageBox::No:
        return false;
      default:
        return false;
    }
}

//add delete button
//add call history viewer

#ifndef DRAWER_H
#define DRAWER_H

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QComboBox>
#include <QMessageBox>
#include <QDateEdit>

#include <memory>

#include "dbhandler.h"
#include "drawerdata.h"
#include "callviewer.h"


enum Status
{
    EMPTY,
    WAITING_REPAIR,
    WAITING_PIECE,
    WAITING_APPROVAL,
    READY
};

enum Awarness
{
    AWARE,
    NOT_AWARE
};

class Drawer : public QWidget
{
    Q_OBJECT
public:
    explicit Drawer(QWidget *parent = nullptr);

    void setup(const int& id, DrawerData& data);
    void loadData(const DrawerData& data);

signals:
    void updated();

private slots:
    void setEditable();
    void saveChange();
    void discardChange();
    void callClient();
    void reset();
    void call_viewer();

private:

    void setReadMode();
    void warning(const char msg[]);

    std::unique_ptr<CallViewer> m_viewer;

    int m_id;
    bool client_aware;

    QLabel* client_awarness;
    QDateEdit* last_call;
    QComboBox* client_awarness_edit;
    QComboBox* status;
    QLineEdit* name;
    QLineEdit* surname;
    QLineEdit* contact;
    QLineEdit* deposit_date;
    QTextEdit* breakdown;
    QTextEdit* complement_info;
    QTextEdit* repair;
    QTextEdit* comments;
    QLineEdit* price;

    QPushButton* modify;
    QPushButton* save;
    QPushButton* discard;
    QPushButton* called;
    QPushButton* reset_drawer;
    QPushButton* view_calls;

    DrawerData* m_data;
    ContactData m_call_data;
};

#endif // DRAWER_H

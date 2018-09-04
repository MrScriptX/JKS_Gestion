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

#include <memory>


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

    void setID(const int& id);
    void loadData(const QJsonObject& json);

signals:
    void updated();

private slots:
    void setEditable();
    void saveChange();
    void discardChange();

private:

    int m_id;
    bool client_aware;

    QLabel* client_awarness;
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
};

#endif // DRAWER_H

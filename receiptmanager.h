#ifndef RECEIPTMANAGER_H
#define RECEIPTMANAGER_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QFile>

#include "Client/clientmanager.h"

class ReceiptManager : public QWidget
{
    Q_OBJECT
public:
    explicit ReceiptManager(QWidget *parent = nullptr);

signals:

public slots:
    void print();
    void fillClient();

private:
    void buildClientBox();
    void buildDepositBox();
    void buildClientReceiptBox();

    QLabel* title;
    QGroupBox* client_box;
    QLabel* subtitle;
    QGroupBox* deposit_box;
    QLabel* receipt_title;
    QGroupBox* receipt_box;

    QLabel* datel;
    QLineEdit* date;
    QLabel* namel;
    QLineEdit* name;
    QLabel* surnamel;
    QLineEdit* surname;
    QLabel* addressl;
    QLineEdit* address;
    QLabel* postal_codel;
    QLineEdit* postal_code;
    QLabel* cityl;
    QLineEdit* city;
    QLabel* phonel;
    QLineEdit* phone;
    QLabel* emaill;
    QLineEdit* email;

    QLabel* mat_typel;//material type
    QLineEdit* mat_type;
    QLabel* passwordl;
    QLineEdit* password;
    QLabel* savel;
    QLineEdit* save;
    QLabel* chargerl;
    QLineEdit* charger;
    QLabel* statel;//physical state
    QTextEdit* state;
    QLabel* breakdownl;
    QTextEdit* breakdown;
    QLabel* operationl;
    QTextEdit* operation;//work done | leave blank

    QLabel* date_depl;//date deposit
    QLineEdit* date_dep;
    QLabel* name_surl;//name and surname
    QLineEdit* name_sur;
    QLabel* mat_type_bisl;
    QLineEdit* mat_type_bis;
    QLabel* brandl;
    QLineEdit* brand;

    QPushButton* m_print;
    QPushButton* m_client;
};

#endif // RECEIPTMANAGER_H

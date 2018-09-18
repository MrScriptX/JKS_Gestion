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

class ReceiptManager : public QWidget
{
    Q_OBJECT
public:
    explicit ReceiptManager(QWidget *parent = nullptr);

signals:

public slots:

private:
    void buildClientBox();

    QLabel* title;
    QGroupBox* client_box;
    QLabel* subtitle;
    QGroupBox* deposit_box;

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

    QPushButton* print;
};

#endif // RECEIPTMANAGER_H

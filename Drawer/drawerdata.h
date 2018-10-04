#ifndef DRAWERDATA_H
#define DRAWERDATA_H

#include <QString>

class DrawerData
{
public:
    DrawerData();

    int getStatus() const;
    void setStatus(int value);

    int getClient_awarness() const;
    void setClient_awarness(int value);

    QString getName() const;
    void setName(const QString &value);

    QString getSurname() const;
    void setSurname(const QString &value);

    QString getContact() const;
    void setContact(const QString &value);

    QString getDeposit_date() const;
    void setDeposit_date(const QString &value);

    QString getBreakdown() const;
    void setBreakdown(const QString &value);

    QString getComplementary_info() const;
    void setComplementary_info(const QString &value);

    QString getRepairs() const;
    void setRepairs(const QString &value);

    QString getComments() const;
    void setComments(const QString &value);

    QString getPrice() const;
    void setPrice(const QString &value);

private:

    int status;
    int client_awarness;
    QString name;
    QString surname;
    QString contact;
    QString deposit_date;
    QString breakdown;
    QString complementary_info;
    QString repairs;
    QString comments;
    QString price;
};

#endif // DRAWERDATA_H

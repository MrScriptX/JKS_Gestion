#include "drawerdata.h"

DrawerData::DrawerData()
{

}

int DrawerData::getStatus() const
{
    return status;
}

void DrawerData::setStatus(int value)
{
    status = value;
}

int DrawerData::getClient_awarness() const
{
    return client_awarness;
}

void DrawerData::setClient_awarness(int value)
{
    client_awarness = value;
}

QString DrawerData::getName() const
{
    return name;
}

void DrawerData::setName(const QString &value)
{
    name = value;
}

QString DrawerData::getSurname() const
{
    return surname;
}

void DrawerData::setSurname(const QString &value)
{
    surname = value;
}

QString DrawerData::getContact() const
{
    return contact;
}

void DrawerData::setContact(const QString &value)
{
    contact = value;
}

QString DrawerData::getDeposit_date() const
{
    return deposit_date;
}

void DrawerData::setDeposit_date(const QString &value)
{
    deposit_date = value;
}

QString DrawerData::getBreakdown() const
{
    return breakdown;
}

void DrawerData::setBreakdown(const QString &value)
{
    breakdown = value;
}

QString DrawerData::getComplementary_info() const
{
    return complementary_info;
}

void DrawerData::setComplementary_info(const QString &value)
{
    complementary_info = value;
}

QString DrawerData::getRepairs() const
{
    return repairs;
}

void DrawerData::setRepairs(const QString &value)
{
    repairs = value;
}

QString DrawerData::getComments() const
{
    return comments;
}

void DrawerData::setComments(const QString &value)
{
    comments = value;
}

QString DrawerData::getPrice() const
{
    return price;
}

void DrawerData::setPrice(const QString &value)
{
    price = value;
}

#ifndef CONTACTDATA_H
#define CONTACTDATA_H

#include <vector>
#include <QDate>

class ContactData
{
public:
    ContactData();


    std::vector<QDate>& dates();
    void setDates(const std::vector<QDate> &dates);

private:
    std::vector<QDate> m_dates;
};

#endif // CONTACTDATA_H

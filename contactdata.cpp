#include "contactdata.h"

ContactData::ContactData()
{

}

std::vector<QDate>& ContactData::dates()
{
    return m_dates;
}

void ContactData::setDates(const std::vector<QDate> &dates)
{
    m_dates = dates;
}

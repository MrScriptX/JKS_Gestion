#ifndef CALLVIEWER_H
#define CALLVIEWER_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>

#include <vector>

#include "dbhandler.h"
#include "contactdata.h"

class CallViewer : public QWidget
{
    Q_OBJECT
public:
    explicit CallViewer(QWidget *parent = nullptr);
    void setup(const QString& filename);
    void load(ContactData& data);

signals:

public slots:

private:
    QString m_filename;
    std::vector<QLineEdit*> m_call_list;
    std::vector<QLabel*> m_labels;
    std::vector<QHBoxLayout*> m_call_boxes;
};

#endif // CALLVIEWER_H

#include "callviewer.h"

CallViewer::CallViewer(QWidget *parent) : QWidget(parent)
{

}

void CallViewer::setup(const QString& filename)
{
    m_filename = filename;
}

void CallViewer::load(ContactData& data)
{
    for(uint32_t i = 0; i < data.dates().size(); i++)
    {
        QLineEdit* line_edit = new QLineEdit;
        line_edit->setReadOnly(true);
        line_edit->setStyleSheet("* { background-color: rgba(0, 0, 0, 0); }");
        line_edit->setText(data.dates()[i].toString());
        QLabel* label = new QLabel;
        label->setText("appelle n°" + QString::number(i));

        m_call_list.push_back(line_edit);
        m_labels.push_back(label);
    }

    for(uint32_t i = 0; i < m_call_list.size(); i++)
    {
        QHBoxLayout* layout = new QHBoxLayout;
        layout->addWidget(m_labels[i]);
        layout->addWidget(m_call_list[i]);
        layout->addStretch();
        m_call_boxes.push_back(layout);
    }

    QVBoxLayout* global = new QVBoxLayout;
    for(uint32_t i = 0; i < m_call_boxes.size(); i++)
    {
        global->addLayout(m_call_boxes[i]);
    }

    setLayout(global);
    show();
}

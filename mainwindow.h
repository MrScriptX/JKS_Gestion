#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QString>
#include <vector>
#include <QFile>
#include <QJsonDocument>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>

#include "drawer.h"
#include "dbhandler.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

    void contextMenuEvent(QContextMenuEvent* event) override;
signals:

public slots:
    void openDrawer(uint32_t i);
    void updateMain();

private slots:
    void reset();

private:
    void setupWindow();

    std::vector<QPushButton*> m_drawers;
    std::vector<DrawerData> m_drawers_data;
    std::unique_ptr<Drawer> m_drawer;

    DBHandler handler;

    QAction* m_reset;
};

#endif // MAINWINDOW_H

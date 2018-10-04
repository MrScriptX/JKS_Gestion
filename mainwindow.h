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
#include <QMenuBar>
#include <QDebug>

#include "Drawer/drawer.h"
#include "Drawer/dbhandler.h"
#include "receiptmanager.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:

public slots:
    void openDrawer(uint32_t i);
    void updateMain();
    void receipt();
    void clientViewer();
    void addClient();

private:
    void setupWindow();
    void createAction();

    std::vector<QPushButton*> m_drawers;
    std::vector<DrawerData> m_drawers_data;
    std::unique_ptr<Drawer> m_drawer;
    std::unique_ptr<ReceiptManager> m_receipt_manager;
    std::unique_ptr<ClientManager> m_cManager;

    DBHandler handler;

    //QAction* m_reset;
    QAction* m_receipt;
    QAction* m_clientView;
    QAction* m_add_client;
    QMenu* m_client_menu;
};

#endif // MAINWINDOW_H

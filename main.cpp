#include <QApplication>
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setApplicationName("JKS Gestion");
    app.setApplicationVersion("v0.1.0");
    app.setWindowIcon(QIcon(":/image/logo.ico"));

    QFile File(":/stylesheets/stylesheet.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());

    app.setStyleSheet(StyleSheet);

    MainWindow window;
    window.show();

    return app.exec();
}

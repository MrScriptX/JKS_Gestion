QT += widgets
QT += core
QT += printsupport

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    contactdata.cpp \
    callviewer.cpp \
    receiptmanager.cpp \
    Client/clientmanager.cpp \
    Drawer/dbhandler.cpp \
    Drawer/drawer.cpp \
    Drawer/drawerdata.cpp

HEADERS += \
    mainwindow.h \
    contactdata.h \
    callviewer.h \
    receiptmanager.h \
    Client/clientmanager.h \
    Drawer/dbhandler.h \
    Drawer/drawer.h \
    Drawer/drawerdata.h

RESOURCES += \
    image.qrc \
    file.qrc

RC_FILE = jks_gestion.rc

DISTFILES +=

QT += widgets
QT += core
QT += printsupport

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    drawer.cpp \
    dbhandler.cpp \
    drawerdata.cpp \
    contactdata.cpp \
    callviewer.cpp \
    receiptmanager.cpp

HEADERS += \
    mainwindow.h \
    drawer.h \
    dbhandler.h \
    drawerdata.h \
    contactdata.h \
    callviewer.h \
    receiptmanager.h

RESOURCES += \
    image.qrc \
    file.qrc

RC_FILE = jks_gestion.rc

DISTFILES +=

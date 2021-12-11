QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dcolumn.cpp \
    dwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    measuringdialog.cpp

HEADERS += \
    dcolumn.h \
    dwindow.h \
    mainwindow.h \
    measuringdialog.h


FORMS += \
    dcolumn.ui \
    dwindow.ui \
    mainwindow.ui \
    measuringdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    clearcache.pyw \
    data.txt \
    exec.pyw \
    learncpp \
    makelist.pyw \
    makesave.pyw \
    pseudocode

QT += testlib
QT += gui
QT += widgets
QT += core

CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_mystack.cpp \
            ../../lab3/mystack.cpp \
            ../../lab3/mainwindow.cpp

HEADERS += ../../lab3/mystack.h \
            ../../lab3/mainwindow.h \
            ../../lab3/ui_mainwindow.h

FORMS += \
        ../../lab3/mainwindow.ui

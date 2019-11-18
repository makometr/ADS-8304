QT += testlib
QT += gui
QT += core
QT += widgets

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_toinfixtest.cpp \
    ../lab3/mainwindow.cpp \
     ../lab3/stack.cpp

HEADERS += ../lab3/mainwindow.h \
            ../lab3/ui_mainwindow.h \
            ../lab3/stack.h

FORMS += ../lab3/mainwindow.ui



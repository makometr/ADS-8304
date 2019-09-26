QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_mystack.cpp \
            ../../lab3/mystack.cpp

HEADERS += ../../lab3/mystack.h

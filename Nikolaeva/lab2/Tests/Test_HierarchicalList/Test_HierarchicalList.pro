QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_test_hierarchicallist.cpp \
            ../../lab2/hierarchicallist.cpp

HEADERS += ../../lab2/hierarchicallist.h

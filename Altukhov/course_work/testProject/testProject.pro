QT += testlib
QT -= gui
QT += core
QT += widgets

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_hashtabletest.cpp

HEADERS += \
    ../hashTableProject/Headers/HashTable.h \
    ../hashTableProject/Headers/qtfiles.h

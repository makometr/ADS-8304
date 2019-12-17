QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_testencodefanoshannon.cpp \
            ../../Source/BinaryTree/Source/fanoshannontree.cpp \
            ../../Source/BinaryTree/Source/encodetree.cpp

HEADERS += ../../Source/BinaryTree/Headers/fanoshannontree.h \
           ../../Source/BinaryTree/Headers/encodetree.h

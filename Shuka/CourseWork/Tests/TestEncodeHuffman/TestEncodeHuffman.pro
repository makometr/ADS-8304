QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_testencodehuffman.cpp \
            ../../Source/BinaryTree/Source/huffmantree.cpp \
            ../../Source/BinaryTree/Source/encodetree.cpp

HEADERS += ../../Source/BinaryTree/Headers/huffmantree.h \
           ../../Source/BinaryTree/Headers/encodetree.h

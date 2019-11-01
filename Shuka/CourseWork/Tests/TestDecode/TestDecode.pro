QT += testlib
QT -= gui
QT += core

CONFIG += qt console warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_testdecode.cpp \
            ../../Source/BinaryTree/Source/decode.cpp \
            ../../Source/BinaryTree/Source/encodetree.cpp

HEADERS += ../../Source/BinaryTree/Headers/decode.h \
           ../../Source/BinaryTree/Headers/encodetree.h

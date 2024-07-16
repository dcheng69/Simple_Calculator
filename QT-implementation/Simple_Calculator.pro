#-------------------------------------------------
#
# Project created by QtCreator 2024-07-13T12:57:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Simple_Calculator
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    button.cpp \
    operation.cpp \
    operation_imp.cpp

HEADERS  += widget.h \
    button.h \
    operation.h \
    operation_imp.h

FORMS    +=

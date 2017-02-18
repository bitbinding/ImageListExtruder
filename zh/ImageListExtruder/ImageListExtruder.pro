#-------------------------------------------------
#
# Project created by QtCreator 2016-05-03T14:11:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageListExtruder
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    imagepreviewwidget.cpp \
    progressdialog.cpp

HEADERS  += mainwindow.h \
    imagepreviewwidget.h \
    exportallthread.h \
    progressdialog.h

FORMS    += mainwindow.ui \
    progressdialog.ui

RC_FILE += ImageListExtruder.rc

DISTFILES += \
    ImageListExtruder.rc

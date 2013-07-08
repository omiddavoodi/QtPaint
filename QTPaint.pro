#-------------------------------------------------
#
# Project created by QtCreator 2013-07-01T13:28:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTPaint
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    drawwidget.cpp \
    colorselector.cpp \
    resizedialog.cpp \
    sliderdialog.cpp

HEADERS  += mainwindow.h \
    drawwidget.h \
    colorselector.h \
    resizedialog.h \
    sliderdialog.h

FORMS    +=

OTHER_FILES += \
    resources.rc

win32:RC_FILE += resources.rc

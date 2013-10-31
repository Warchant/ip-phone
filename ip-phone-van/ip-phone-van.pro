#-------------------------------------------------
#
# Project created by QtCreator 2013-10-03T18:01:15
#
#-------------------------------------------------

QT       += core gui multimedia printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ip-phone-van
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        wav.cpp \
        AudioInput.cpp \
        AudioIO.cpp \
        AudioOutput.cpp \
        Channel.cpp \
        RepairAlgorithm.cpp \
        qcustomplot.cpp \
        dialog_info.cpp \
        functions.cpp

HEADERS  += mainwindow.h \
        wav.h \
        AudioInput.h \
        AudioIO.h \
        AudioOutput.h \
        Channel.h \
        RepairAlgorithm.h \
        qcustomplot.h \
        dialog_info.h \
        functions.h

FORMS    += mainwindow.ui \
    dialog_info.ui

OTHER_FILES +=

RESOURCES += \
    recources.qrc

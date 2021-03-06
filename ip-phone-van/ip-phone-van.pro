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
        AudioIO.cpp \
        RepairAlgorithm.cpp \
        qcustomplot.cpp \
        dialog_info.cpp \
        functions.cpp \
    dialog_packetdelete.cpp \
    packets.cpp \
    dialog_packetrecovery.cpp \
    dialog_noiseinfo.cpp

HEADERS  += mainwindow.h \
        wav.h \
        AudioIO.h \
        RepairAlgorithm.h \
        qcustomplot.h \
        dialog_info.h \
        functions.h \
    dialog_packetdelete.h \
    packets.h \
    dialog_packetrecovery.h \
    dialog_noiseinfo.h

FORMS    += mainwindow.ui \
    dialog_info.ui \
    dialog_packetdelete.ui \
    dialog_packetrecovery.ui \
    dialog_noiseinfo.ui

OTHER_FILES +=

CONFIG += c++11

RESOURCES += \
    recources.qrc

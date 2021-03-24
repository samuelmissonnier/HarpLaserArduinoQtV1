QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# set common library path

CONFIG += c++11

TARGET = Serial_RGB_Qt
TEMPLATE = app

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    manualpage.cpp \
    automaticpage.cpp

HEADERS += \
    mainwindow.h \
    manualpage.h \
    automaticpage.h

FORMS += \
    mainwindow.ui \
    manualpage.ui \
    automaticpage.ui


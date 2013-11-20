#-------------------------------------------------
# Project created by QtCreator 2011-03-20T19:19:49
#-------------------------------------------------

QT       += core gui

TARGET = AQModBus
TEMPLATE = app
VERSION = 0.1.90
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

SOURCES         += main.cpp\
                aqmodbus.cpp \
                modbussettings.cpp \
                libmodbus/modbus.c \
                QLedMatrix-0.6/qledmatrix.cpp

HEADERS         += aqmodbus.h \
                libmodbus/modbus.h \
                QLedMatrix-0.6/qledmatrix.h

INCLUDEPATH     += libmodbus

FORMS           += aqmodbus.ui \
                modbussettings.ui

OTHER_FILES += \
    android/AndroidManifest.xml \
    android/res/drawable-hdpi/icon.png \
    android/res/drawable-ldpi/icon.png \
    android/res/drawable-mdpi/icon.png \
    android/res/values/libs.xml \
    android/res/values/strings.xml \
    android/src/eu/licentia/necessitas/industrius/QtActivity.java \
    android/src/eu/licentia/necessitas/industrius/QtApplication.java \
    android/src/eu/licentia/necessitas/industrius/QtSurface.java \
    android/src/eu/licentia/necessitas/ministro/IMinistro.aidl \
    android/src/eu/licentia/necessitas/ministro/IMinistroCallback.aidl \
    qtc_packaging/debian_fremantle/rules \
    qtc_packaging/debian_fremantle/README \
    qtc_packaging/debian_fremantle/copyright \
    qtc_packaging/debian_fremantle/control \
    qtc_packaging/debian_fremantle/compat \
    qtc_packaging/debian_fremantle/changelog

maemo5 {
    target.path = /opt/AQModBus/bin
    INSTALLS += target
}

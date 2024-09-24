QT -= gui

CONFIG += c++1z
CONFIG -= app_bundle

QMAKE_CXXFLAGS += -std=c++1z

SOURCES += \
        main.cpp \
    process.cpp

HEADERS += \
    process.h

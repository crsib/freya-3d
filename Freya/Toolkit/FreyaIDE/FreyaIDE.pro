# -------------------------------------------------
# Project created by QtCreator 2009-07-02T21:15:05
# -------------------------------------------------
QT += opengl \
    xml
debug:build_postfix = debug
release:build_postfix = release
TARGET = FreyaIDE
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    preferences.cpp
HEADERS += mainwindow.h \
    preferences.h
FORMS += mainwindow.ui \
    preferences.ui
INCLUDEPATH += .
macx:INCLUDEPATH += /usr/local/lib/boost-1_39
MOC_DIR = ./QTO/MOC
UI_DIR = ./QTO/UIC
RCC_DIR = ./QTO/RCC
OBJECTS_DIR = ./QTO/build/$$build_postfix
RESOURCES += icons.qrc

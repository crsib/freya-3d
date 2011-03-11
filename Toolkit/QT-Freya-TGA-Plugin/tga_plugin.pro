TARGET = qftga

TEMPLATE = lib

CONFIG += static qt plugin

INCLUDEPATH += . \

MOC_DIR = ./QTO/MOC

UI_DIR = ./QTO/UIC

RCC_DIR = ./QTO/RCC

SOURCES += main.cpp \
		   fqtgahandler.cpp\
		   
HEADERS += fqtgahandler.h
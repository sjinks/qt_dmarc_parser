QT      += testlib
QT      -= gui
TARGET   = tst_dmarcparser
CONFIG  += console
CONFIG  -= app_bundle
TEMPLATE = app

lessThan(QT_MAJOR_VERSION, 5): CONFIG += qtestlib

SOURCES += \
	parsertest.cpp

RESOURCES += \
	testdata.qrc

include(../src/dmarcparser.pri)

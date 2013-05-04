QT      -= gui
TARGET   = dmarcparser
TEMPLATE = lib
VERSION  = 1.0.0
DEFINES += DMARCPARSER_LIBRARY

include(dmarcparser.pri)

TRANSLATIONS += \
	dmarcparser_ru.ts \
	dmarcparser_ua.ts

unix:!symbian {
	maemo5 {
		target.path = /opt/usr/lib
	} else {
		target.path = /usr/lib
	}

	INSTALLS += target
}

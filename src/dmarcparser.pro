QT      -= gui
TARGET   = dmarcparser
TEMPLATE = lib
VERSION  = 1.0.0
DEFINES += DMARCPARSER_LIBRARY

include(dmarcparser.pri)

TRANSLATIONS += \
	dmarcparser_ru.ts \
	dmarcparser_ua.ts

target.files += dmarcparser_ru.qm dmarcparser_ua.qm

isEmpty(QMAKE_LRELEASE) {
	win32:QMAKE_LRELEASE = $$[QT_INSTALL_BINS]\lrelease.exe
	else:QMAKE_LRELEASE = $$[QT_INSTALL_BINS]/lrelease
}

updateqm.input    = TRANSLATIONS
updateqm.output   = ${QMAKE_FILE_PATH}/${QMAKE_FILE_BASE}.qm
updateqm.commands = $$QMAKE_LRELEASE ${QMAKE_FILE_IN} -qm ${QMAKE_FILE_PATH}/${QMAKE_FILE_BASE}.qm
updateqm.CONFIG  += no_link target_predeps
QMAKE_EXTRA_COMPILERS += updateqm

unix:!symbian {
	maemo5 {
		target.path = /opt/usr/lib
	} else {
		target.path = /usr/lib
	}

	INSTALLS += target
}

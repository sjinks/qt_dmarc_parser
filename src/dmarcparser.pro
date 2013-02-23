QT      -= gui
TARGET   = dmarcparser
TEMPLATE = lib
VERSION  = 1.0.0
DEFINES += DMARCPARSER_LIBRARY

SOURCES += \
	dmarcparser.cpp \
	reportmetadata.cpp \
	reportmetadata_p.cpp \
	publishedpolicy.cpp \
	publishedpolicy_p.cpp \
	recordidentifier.cpp \
	recordidentifier_p.cpp \
	overridereason.cpp \
	overridereason_p.cpp \
	evaluatedpolicy.cpp \
	private.cpp \
	evaluatedpolicy_p.cpp \
	recordrow.cpp \
	recordrow_p.cpp \
	dkimauthenticationresult.cpp \
	dkimauthenticationresult_p.cpp \
	spfauthenticationresult.cpp \
	spfauthenticationresult_p.cpp \
	authenticationresults.cpp \
	authenticationresults_p.cpp \
	record.cpp \
	record_p.cpp \
	feedback.cpp \
	feedback_p.cpp

HEADERS += \
	dmarcparser.h\
	reportmetadata.h \
	reportmetadata_p.h \
	publishedpolicy.h \
	publishedpolicy_p.h \
	recordidentifier.h \
	recordidentifier_p.h \
	overridereason.h \
	overridereason_p.h \
	evaluatedpolicy.h \
	private.h \
	evaluatedpolicy_p.h \
	recordrow.h \
	recordrow_p.h \
	dkimauthenticationresult.h \
	dkimauthenticationresult_p.h \
	spfauthenticationresult.h \
	spfauthenticationresult_p.h \
	authenticationresults.h \
	authenticationresults_p.h \
	record.h \
	record_p.h \
	feedback.h \
	feedback_p.h

unix:!symbian {
	maemo5 {
		target.path = /opt/usr/lib
	} else {
		target.path = /usr/lib
	}

	INSTALLS += target
}

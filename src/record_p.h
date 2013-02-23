#ifndef DMARC_RECORD_P_H
#define DMARC_RECORD_P_H

#include <QtCore/QList>
#include <QtCore/QSharedData>
#include "dmarcparser.h"
#include "recordidentifier.h"
#include "authenticationresults.h"

QT_FORWARD_DECLARE_CLASS(QXmlStreamReader)

namespace DMARC {

class Q_DECL_HIDDEN RecordPrivate : public QSharedData {
public:
	RecordPrivate(void);
	bool parse(QXmlStreamReader& r);

	QList<DMARC::RecordRow> rows;
	DMARC::RecordIdentifier identifiers;
	DMARC::AuthenticationResults auth_results;
};

} // namespace DMARC

#endif // DMARC_RECORD_P_H

#ifndef DMARC_DKIMAUTHENTICATIONRESULT_P_H
#define DMARC_DKIMAUTHENTICATIONRESULT_P_H

#include <QtCore/QSharedData>
#include <QtCore/QString>
#include "dmarcparser.h"

QT_FORWARD_DECLARE_CLASS(QXmlStreamReader)

namespace DMARC {

class Q_DECL_HIDDEN DKIMAuthenticationResultPrivate : public QSharedData {
public:
	DKIMAuthenticationResultPrivate(void);
	bool parse(QXmlStreamReader& r);

	QString domain;
	DMARC::DKIMAuthResult result;
	QString human_result;
};

} // namespace DMARC

#endif // DMARC_DKIMAUTHENTICATIONRESULT_P_H

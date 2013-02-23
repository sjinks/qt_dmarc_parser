#ifndef DMARC_AUTHENTICATIONRESULTS_P_H
#define DMARC_AUTHENTICATIONRESULTS_P_H

#include <QtCore/QList>
#include <QtCore/QSharedData>
#include "dmarcparser.h"

QT_FORWARD_DECLARE_CLASS(QXmlStreamReader)

namespace DMARC {

class Q_DECL_HIDDEN AuthenticationResultsPrivate : public QSharedData {
public:
	AuthenticationResultsPrivate(void);
	bool parse(QXmlStreamReader& r);

	QList<DKIMAuthenticationResult> dkim;
	QList<SPFAuthenticationResult> spf;
};

} // namespace DMARC

#endif // DMARC_AUTHENTICATIONRESULTS_P_H

#ifndef DMARC_SPFAUTHENTICATIONRESULT_P_H
#define DMARC_SPFAUTHENTICATIONRESULT_P_H

#include <QtCore/QSharedData>
#include <QtCore/QString>
#include "dmarcparser.h"

QT_FORWARD_DECLARE_CLASS(QXmlStreamReader)

namespace DMARC {

class Q_DECL_HIDDEN SPFAuthenticationResultPrivate : public QSharedData {
public:
	SPFAuthenticationResultPrivate(void);
	bool parse(QXmlStreamReader& r);

	QString domain;
	DMARC::SPFAuthResult result;
};

} // namespace DMARC

#endif // DMARC_SPFAUTHENTICATIONRESULT_P_H

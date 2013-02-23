#ifndef DMARC_AUTHENTICATIONRESULTS_H
#define DMARC_AUTHENTICATIONRESULTS_H

#include <QtCore/QExplicitlySharedDataPointer>
#include <QtCore/QList>
#include "dmarcparser.h"

namespace DMARC {

class AuthenticationResultsPrivate;

class DMARCPARSERSHARED_EXPORT AuthenticationResults {
public:
	AuthenticationResults(void);
	~AuthenticationResults(void);

	const QList<DKIMAuthenticationResult>& dkim(void) const;
	const QList<SPFAuthenticationResult>& spf(void) const;
private:
	Q_DECLARE_PRIVATE(AuthenticationResults)
	QExplicitlySharedDataPointer<AuthenticationResultsPrivate> d_ptr;

	friend class RecordPrivate;
};

} // namespace DMARC

#endif // DMARC_AUTHENTICATIONRESULTS_H

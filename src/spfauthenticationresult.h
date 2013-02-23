#ifndef DMARC_SPFAUTHENTICATIONRESULT_H
#define DMARC_SPFAUTHENTICATIONRESULT_H

#include <QtCore/QExplicitlySharedDataPointer>
#include "dmarcparser.h"

namespace DMARC {

class SPFAuthenticationResultPrivate;

class DMARCPARSERSHARED_EXPORT SPFAuthenticationResult {
public:
	SPFAuthenticationResult(void);
	~SPFAuthenticationResult(void);

	QString domain(void) const;
	DMARC::SPFAuthResult result(void) const;
private:
	Q_DECLARE_PRIVATE(SPFAuthenticationResult)
	QExplicitlySharedDataPointer<SPFAuthenticationResultPrivate> d_ptr;

	friend class AuthenticationResultsPrivate;
};

} // namespace DMARC

#endif // DMARC_SPFAUTHENTICATIONRESULT_H

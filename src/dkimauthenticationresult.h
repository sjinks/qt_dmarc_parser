#ifndef DMARC_DKIMAUTHENTICATIONRESULT_H
#define DMARC_DKIMAUTHENTICATIONRESULT_H

#include <QtCore/QExplicitlySharedDataPointer>
#include "dmarcparser.h"

namespace DMARC {

class DKIMAuthenticationResultPrivate;

class DMARCPARSERSHARED_EXPORT DKIMAuthenticationResult {
public:
	DKIMAuthenticationResult(void);
	~DKIMAuthenticationResult(void);

	QString domain(void) const;
	DMARC::DKIMAuthResult result(void) const;
	QString humanResult(void) const;

private:
	Q_DECLARE_PRIVATE(DKIMAuthenticationResult)
	QExplicitlySharedDataPointer<DKIMAuthenticationResultPrivate> d_ptr;

	friend class AuthenticationResultsPrivate;
};

} // namespace DMARC

#endif // DMARC_DKIMAUTHENTICATIONRESULT_H

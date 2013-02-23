#include "spfauthenticationresult.h"
#include "spfauthenticationresult_p.h"

DMARC::SPFAuthenticationResult::SPFAuthenticationResult(void)
	: d_ptr(new DMARC::SPFAuthenticationResultPrivate())
{
}

DMARC::SPFAuthenticationResult::~SPFAuthenticationResult(void)
{
}

QString DMARC::SPFAuthenticationResult::domain(void) const
{
	Q_D(const DMARC::SPFAuthenticationResult);
	return d->domain;
}

DMARC::SPFAuthResult DMARC::SPFAuthenticationResult::result(void) const
{
	Q_D(const DMARC::SPFAuthenticationResult);
	return d->result;
}

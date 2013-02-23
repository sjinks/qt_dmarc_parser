#include "authenticationresults.h"
#include "authenticationresults_p.h"
#include "dkimauthenticationresult.h"
#include "spfauthenticationresult.h"

DMARC::AuthenticationResults::AuthenticationResults(void)
	: d_ptr(new DMARC::AuthenticationResultsPrivate())
{
}

DMARC::AuthenticationResults::~AuthenticationResults(void)
{
}

const QList<DMARC::DKIMAuthenticationResult>& DMARC::AuthenticationResults::dkim(void) const
{
	Q_D(const DMARC::AuthenticationResults);
	return d->dkim;
}

const QList<DMARC::SPFAuthenticationResult>& DMARC::AuthenticationResults::spf(void) const
{
	Q_D(const DMARC::AuthenticationResults);
	return d->spf;
}

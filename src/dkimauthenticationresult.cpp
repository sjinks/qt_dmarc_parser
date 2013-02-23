#include "dkimauthenticationresult.h"
#include "dkimauthenticationresult_p.h"

DMARC::DKIMAuthenticationResult::DKIMAuthenticationResult(void)
	: d_ptr(new DMARC::DKIMAuthenticationResultPrivate())
{
}

DMARC::DKIMAuthenticationResult::~DKIMAuthenticationResult(void)
{
}

QString DMARC::DKIMAuthenticationResult::domain(void) const
{
	Q_D(const DMARC::DKIMAuthenticationResult);
	return d->domain;
}

DMARC::DKIMAuthResult DMARC::DKIMAuthenticationResult::result(void) const
{
	Q_D(const DMARC::DKIMAuthenticationResult);
	return d->result;
}

QString DMARC::DKIMAuthenticationResult::humanResult(void) const
{
	Q_D(const DMARC::DKIMAuthenticationResult);
	return d->human_result;
}

#include "overridereason.h"
#include "overridereason_p.h"

DMARC::OverrideReason::OverrideReason(void)
	: d_ptr(new DMARC::OverrideReasonPrivate())
{
}

DMARC::OverrideReason::~OverrideReason(void)
{
}

DMARC::OverrideType DMARC::OverrideReason::type(void) const
{
	Q_D(const DMARC::OverrideReason);
	return d->type;
}

QString DMARC::OverrideReason::comment(void) const
{
	Q_D(const DMARC::OverrideReason);
	return d->comment;
}

#include "evaluatedpolicy.h"
#include "evaluatedpolicy_p.h"
#include "overridereason.h"

DMARC::EvaluatedPolicy::EvaluatedPolicy(void)
	: d_ptr(new DMARC::EvaluatedPolicyPrivate())
{
}

DMARC::EvaluatedPolicy::~EvaluatedPolicy(void)
{
}

DMARC::Disposition DMARC::EvaluatedPolicy::disposition(void) const
{
	Q_D(const DMARC::EvaluatedPolicy);
	return d->disposition;
}

DMARC::Outcome DMARC::EvaluatedPolicy::dkim(void) const
{
	Q_D(const DMARC::EvaluatedPolicy);
	return d->dkim;
}

DMARC::Outcome DMARC::EvaluatedPolicy::spf(void) const
{
	Q_D(const DMARC::EvaluatedPolicy);
	return d->spf;
}

const QList<DMARC::OverrideReason>& DMARC::EvaluatedPolicy::reasons(void) const
{
	Q_D(const DMARC::EvaluatedPolicy);
	return d->reasons;
}

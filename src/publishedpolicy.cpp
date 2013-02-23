#include "publishedpolicy.h"
#include "publishedpolicy_p.h"

DMARC::PublishedPolicy::PublishedPolicy(void)
	: d_ptr(new DMARC::PublishedPolicyPrivate())
{
}

DMARC::PublishedPolicy::~PublishedPolicy(void)
{
}

QString DMARC::PublishedPolicy::domain(void) const
{
	Q_D(const DMARC::PublishedPolicy);
	return d->domain;
}

DMARC::Policy DMARC::PublishedPolicy::adkim(void) const
{
	Q_D(const DMARC::PublishedPolicy);
	return d->adkim;
}

DMARC::Policy DMARC::PublishedPolicy::aspf(void) const
{
	Q_D(const DMARC::PublishedPolicy);
	return d->aspf;
}

DMARC::Disposition DMARC::PublishedPolicy::p(void) const
{
	Q_D(const DMARC::PublishedPolicy);
	return d->p;
}

DMARC::Disposition DMARC::PublishedPolicy::sp() const
{
	Q_D(const DMARC::PublishedPolicy);
	return d->sp;
}

int DMARC::PublishedPolicy::pct(void) const
{
	Q_D(const DMARC::PublishedPolicy);
	return d->pct;
}

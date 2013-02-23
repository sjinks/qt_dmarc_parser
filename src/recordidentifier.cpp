#include "recordidentifier.h"
#include "recordidentifier_p.h"

DMARC::RecordIdentifier::RecordIdentifier(void)
	: d_ptr(new DMARC::RecordIdentifierPrivate())
{
}

DMARC::RecordIdentifier::~RecordIdentifier(void)
{
}

QString DMARC::RecordIdentifier::envelopeTo(void) const
{
	Q_D(const DMARC::RecordIdentifier);
	return d->envelope_to;
}

QString DMARC::RecordIdentifier::headerFrom(void) const
{
	Q_D(const DMARC::RecordIdentifier);
	return d->header_from;
}

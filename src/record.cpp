#include "record.h"
#include "record_p.h"
#include "recordrow.h"

DMARC::Record::Record(void)
	: d_ptr(new DMARC::RecordPrivate())
{
}

DMARC::Record::~Record(void)
{
}

const QList<DMARC::RecordRow>& DMARC::Record::rows(void) const
{
	Q_D(const DMARC::Record);
	return d->rows;
}

const DMARC::RecordIdentifier& DMARC::Record::identifiers(void) const
{
	Q_D(const DMARC::Record);
	return d->identifiers;
}

const DMARC::AuthenticationResults &DMARC::Record::authResults(void) const
{
	Q_D(const DMARC::Record);
	return d->auth_results;
}

#include "recordrow.h"
#include "recordrow_p.h"

DMARC::RecordRow::RecordRow(void)
	: d_ptr(new DMARC::RecordRowPrivate())
{
}

DMARC::RecordRow::~RecordRow(void)
{
}

QString DMARC::RecordRow::sourceIP(void) const
{
	Q_D(const DMARC::RecordRow);
	return d->source_ip;
}

int DMARC::RecordRow::count(void) const
{
	Q_D(const DMARC::RecordRow);
	return d->count;
}

const DMARC::EvaluatedPolicy* DMARC::RecordRow::evaluatedPolicy(void) const
{
	Q_D(const DMARC::RecordRow);
	if (d->has_policy) {
		return &d->evaluated_policy;
	}

	return 0;
}

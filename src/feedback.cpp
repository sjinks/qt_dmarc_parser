#include "feedback.h"
#include "feedback_p.h"
#include "record.h"

DMARC::Feedback::Feedback(void)
	: d_ptr(new FeedbackPrivate())
{
}

DMARC::Feedback::~Feedback(void)
{
}

const DMARC::ReportMetadata& DMARC::Feedback::metadata(void) const
{
	Q_D(const DMARC::Feedback);
	return d->metadata;
}

const DMARC::PublishedPolicy& DMARC::Feedback::policy(void) const
{
	Q_D(const DMARC::Feedback);
	return d->policy;
}

const QList<DMARC::Record>& DMARC::Feedback::records(void) const
{
	Q_D(const DMARC::Feedback);
	return d->records;
}

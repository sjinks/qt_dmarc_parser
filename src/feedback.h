#ifndef DMARC_FEEDBACK_H
#define DMARC_FEEDBACK_H

#include <QtCore/QExplicitlySharedDataPointer>
#include <QtCore/QList>
#include "dmarcparser.h"

namespace DMARC {

class FeedbackPrivate;

class DMARCPARSERSHARED_EXPORT Feedback {
public:
	Feedback(void);
	~Feedback(void);

	const DMARC::ReportMetadata& metadata(void) const;
	const DMARC::PublishedPolicy& policy(void) const;
	const QList<DMARC::Record>& records(void) const;

private:
	Q_DECLARE_PRIVATE(Feedback)
	QExplicitlySharedDataPointer<FeedbackPrivate> d_ptr;

	friend class ReportParser;
};

} // namespace DMARC

#endif // DMARC_FEEDBACK_H

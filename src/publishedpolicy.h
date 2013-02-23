#ifndef DMARC_PUBLISHEDPOLICY_H
#define DMARC_PUBLISHEDPOLICY_H

#include <QtCore/QExplicitlySharedDataPointer>
#include "dmarcparser.h"

namespace DMARC {

class PublishedPolicyPrivate;

class DMARCPARSERSHARED_EXPORT PublishedPolicy {
public:
	PublishedPolicy(void);
	~PublishedPolicy(void);

	QString domain(void) const;
	DMARC::Policy adkim(void) const;
	DMARC::Policy aspf(void) const;
	DMARC::Disposition p(void) const;
	DMARC::Disposition sp(void) const;
	int pct(void) const;

private:
	Q_DECLARE_PRIVATE(PublishedPolicy)
	QExplicitlySharedDataPointer<PublishedPolicyPrivate> d_ptr;

	friend class FeedbackPrivate;
};

} // namespace DMARC

#endif // DMARC_PUBLISHEDPOLICY_H

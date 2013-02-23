#ifndef DMARC_EVALUATEDPOLICY_H
#define DMARC_EVALUATEDPOLICY_H

#include <QtCore/QExplicitlySharedDataPointer>
#include <QtCore/QList>
#include "dmarcparser.h"

namespace DMARC {

class EvaluatedPolicyPrivate;

class DMARCPARSERSHARED_EXPORT EvaluatedPolicy {
public:
	EvaluatedPolicy(void);
	~EvaluatedPolicy(void);

	DMARC::Disposition disposition(void) const;
	DMARC::Outcome dkim(void) const;
	DMARC::Outcome spf(void) const;
	const QList<DMARC::OverrideReason>& reasons(void) const;

private:
	Q_DECLARE_PRIVATE(EvaluatedPolicy)
	QExplicitlySharedDataPointer<EvaluatedPolicyPrivate> d_ptr;

	friend class RecordRowPrivate;
};

} // namespace DMARC

#endif // DMARC_EVALUATEDPOLICY_H

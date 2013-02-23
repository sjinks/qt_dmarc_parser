#ifndef DMARC_OVERRIDEREASON_H
#define DMARC_OVERRIDEREASON_H

#include <QtCore/QExplicitlySharedDataPointer>
#include "dmarcparser.h"

namespace DMARC {

class OverrideReasonPrivate;

class DMARCPARSERSHARED_EXPORT OverrideReason {
public:
	OverrideReason(void);
	~OverrideReason(void);

	DMARC::OverrideType type(void) const;
	QString comment(void) const;

private:
	Q_DECLARE_PRIVATE(OverrideReason)
	QExplicitlySharedDataPointer<OverrideReasonPrivate> d_ptr;

	friend class EvaluatedPolicyPrivate;
};

} // namespace DMARC

#endif // DMARC_OVERRIDEREASON_H

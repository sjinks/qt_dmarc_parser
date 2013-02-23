#ifndef DMARC_EVALUATEDPOLICY_P_H
#define DMARC_EVALUATEDPOLICY_P_H

#include <QtCore/QList>
#include <QtCore/QSharedData>
#include "dmarcparser.h"

QT_FORWARD_DECLARE_CLASS(QXmlStreamReader)

namespace DMARC {

class Q_DECL_HIDDEN EvaluatedPolicyPrivate : public QSharedData {
public:
	EvaluatedPolicyPrivate(void);
	bool parse(QXmlStreamReader& r);

	DMARC::Disposition disposition;
	DMARC::Outcome dkim;
	DMARC::Outcome spf;
	QList<DMARC::OverrideReason> reasons;
};

} // namespace DMARC

#endif // DMARC_EVALUATEDPOLICY_P_H

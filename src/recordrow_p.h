#ifndef DMARC_RECORDROW_P_H
#define DMARC_RECORDROW_P_H

#include <QtCore/QSharedData>
#include <QtCore/QString>
#include "evaluatedpolicy.h"

QT_FORWARD_DECLARE_CLASS(QXmlStreamReader)

namespace DMARC {

class Q_DECL_HIDDEN RecordRowPrivate : public QSharedData {
public:
	RecordRowPrivate(void);
	bool parse(QXmlStreamReader& r);

	QString source_ip;
	int count;
	EvaluatedPolicy evaluated_policy;
	bool has_policy;
};

} // namespace DMARC

#endif // DMARC_RECORDROW_P_H

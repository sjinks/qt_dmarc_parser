#ifndef DMARC_RECORDROW_H
#define DMARC_RECORDROW_H

#include <QtCore/QExplicitlySharedDataPointer>
#include "dmarcparser.h"

namespace DMARC {

class EvaluatedPolicy;
class RecordRowPrivate;

class DMARCPARSERSHARED_EXPORT RecordRow {
public:
	RecordRow(void);
	~RecordRow(void);

	QString sourceIP(void) const;
	int count(void) const;
	const EvaluatedPolicy* evaluatedPolicy(void) const;

private:
	Q_DECLARE_PRIVATE(RecordRow)
	QExplicitlySharedDataPointer<RecordRowPrivate> d_ptr;

	friend class RecordPrivate;
};

} // namespace DMARC

#endif // DMARC_RECORDROW_H

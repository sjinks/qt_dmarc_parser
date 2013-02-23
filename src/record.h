#ifndef DMARC_RECORD_H
#define DMARC_RECORD_H

#include <QtCore/QExplicitlySharedDataPointer>
#include <QtCore/QList>
#include "dmarcparser.h"

namespace DMARC {

class RecordPrivate;

class DMARCPARSERSHARED_EXPORT Record {
public:
	Record(void);
	~Record(void);

	const QList<DMARC::RecordRow>& rows(void) const;
	const DMARC::RecordIdentifier& identifiers(void) const;
	const DMARC::AuthenticationResults& authResults(void) const;

private:
	Q_DECLARE_PRIVATE(Record)
	QExplicitlySharedDataPointer<RecordPrivate> d_ptr;

	friend class FeedbackPrivate;
};

} // namespace DMARC

#endif // DMARC_RECORD_H

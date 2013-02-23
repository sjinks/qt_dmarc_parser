#ifndef DMARC_RECORDIDENTIFIER_H
#define DMARC_RECORDIDENTIFIER_H

#include <QtCore/QExplicitlySharedDataPointer>
#include "dmarcparser.h"

namespace DMARC {

class RecordIdentifierPrivate;

class DMARCPARSERSHARED_EXPORT RecordIdentifier {
public:
	RecordIdentifier(void);
	~RecordIdentifier(void);

	QString envelopeTo(void) const;
	QString headerFrom(void) const;
private:
	Q_DECLARE_PRIVATE(RecordIdentifier)
	QExplicitlySharedDataPointer<RecordIdentifierPrivate> d_ptr;

	friend class RecordPrivate;
};

} // namespace DMARC

#endif // DMARC_RECORDIDENTIFIER_H

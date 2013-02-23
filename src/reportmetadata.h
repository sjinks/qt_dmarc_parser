#ifndef DMARC_REPORTMETADATA_H
#define DMARC_REPORTMETADATA_H

#include <QtCore/QExplicitlySharedDataPointer>
#include <QtCore/QPair>
#include <QtCore/QStringList>
#include "dmarcparser.h"

namespace DMARC {

class ReportMetadataPrivate;

class DMARCPARSERSHARED_EXPORT ReportMetadata {
public:
	ReportMetadata(void);
	~ReportMetadata(void);

	QString orgName(void) const;
	QString email(void) const;
	QString extraContactInfo(void) const;
	QString reportID(void) const;
	const QPair<qulonglong, qulonglong>& dateRange(void) const;
	const QStringList& errors(void) const;
private:
	Q_DECLARE_PRIVATE(ReportMetadata)
	QExplicitlySharedDataPointer<ReportMetadataPrivate> d_ptr;

	friend class FeedbackPrivate;
};

} // namespace DMARC

#endif // DMARC_REPORTMETADATA_H

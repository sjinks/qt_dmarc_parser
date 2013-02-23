#ifndef DMARC_FEEDBACK_P_H
#define DMARC_FEEDBACK_P_H

#include <QtCore/QList>
#include <QtCore/QSharedData>
#include "dmarcparser.h"
#include "reportmetadata.h"
#include "publishedpolicy.h"

QT_FORWARD_DECLARE_CLASS(QXmlStreamReader)

namespace DMARC {

class Q_DECL_HIDDEN FeedbackPrivate : public QSharedData {
public:
	FeedbackPrivate(void);
	bool parse(QXmlStreamReader& r);

	DMARC::ReportMetadata metadata;
	DMARC::PublishedPolicy policy;
	QList<DMARC::Record> records;
};

} // namespace DMARC

#endif // DMARC_FEEDBACK_P_H

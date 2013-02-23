#include <QtCore/QXmlStreamReader>
#include "feedback_p.h"
#include "record.h"
#include "record_p.h"
#include "recordrow.h"
#include "reportmetadata_p.h"
#include "publishedpolicy_p.h"

DMARC::FeedbackPrivate::FeedbackPrivate(void)
	: QSharedData(), metadata(), policy(), records()
{
}

bool DMARC::FeedbackPrivate::parse(QXmlStreamReader& r)
{
	while (r.readNextStartElement()) {
		if (r.name() == QLatin1String("report_metadata")) {
			this->metadata.d_func()->parse(r);
		}
		else if (r.name() == QLatin1String("policy_published")) {
			this->policy.d_func()->parse(r);
		}
		else if (r.name() == QLatin1String("record")) {
			DMARC::Record rec;
			if (rec.d_func()->parse(r)) {
				this->records.append(rec);
			}
		}
		else {
			r.raiseError(QString::fromLatin1("Unexpected element %1").arg(r.name().toString()));
		}
	}

	return !r.hasError();
}

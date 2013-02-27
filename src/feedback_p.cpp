#include <QtCore/QCoreApplication>
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
	bool seen_rm  = false;
	bool seen_pp  = false;
	bool seen_rec = false;
	while (r.readNextStartElement()) {
		if (r.name() == QLatin1String("report_metadata")) {
			if (!seen_rm) {
				seen_rm = true;
				this->metadata.d_func()->parse(r);
			}
			else {
				r.raiseError(QCoreApplication::translate("dmarcparser", "Duplicate <report_metadata> tag"));
			}
		}
		else if (r.name() == QLatin1String("policy_published")) {
			if (!seen_pp) {
				seen_pp = true;
				this->policy.d_func()->parse(r);
			}
			else {
				r.raiseError(QCoreApplication::translate("dmarcparser", "Duplicate <policy_published> tag"));
			}
		}
		else if (r.name() == QLatin1String("record")) {
			DMARC::Record rec;
			seen_rec = true;
			if (rec.d_func()->parse(r)) {
				this->records.append(rec);
			}
		}
		else {
			r.raiseError(QCoreApplication::translate("dmarcparser", "Unexpected element <%1>").arg(r.name().toString()));
		}
	}

	if (!r.hasError()) {
		if (!seen_rm) {
			r.raiseError(QCoreApplication::translate("dmarcparser", "No report_metadata tag"));
		}
		else if (!seen_pp) {
			r.raiseError(QCoreApplication::translate("dmarcparser", "No policy_published tag"));
		}
		else if (!seen_rec) {
			r.raiseError(QCoreApplication::translate("dmarcparser", "No record tag"));
		}
	}

	return !r.hasError();
}

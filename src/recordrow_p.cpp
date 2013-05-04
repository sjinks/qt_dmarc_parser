#include <QtCore/QCoreApplication>
#include <QtCore/QXmlStreamReader>
#include "recordrow_p.h"
#include "evaluatedpolicy.h"
#include "evaluatedpolicy_p.h"

DMARC::RecordRowPrivate::RecordRowPrivate(void)
	: QSharedData(), source_ip(), count(0), evaluated_policy(), has_policy(false)
{
}

bool DMARC::RecordRowPrivate::parse(QXmlStreamReader& r)
{
	bool seen_sourceip = false;
	bool seen_count    = false;

	while (r.readNextStartElement()) {
		if (r.name() == QLatin1String("source_ip")) {
			if (!seen_sourceip) {
				seen_sourceip   = true;
				this->source_ip = r.readElementText();
			}
			else {
				r.raiseError(QCoreApplication::translate("dmarcparser", "Duplicate <%1> tag").arg(QLatin1String("source_ip")));
			}
		}
		else if (r.name() == QLatin1String("count")) {
			if (!seen_count) {
				seen_count  = true;
				bool ok     = false;
				QString val = r.readElementText();
				this->count = val.toInt(&ok);

				if (!ok) {
					r.raiseError(QCoreApplication::translate("dmarcparser", "Value '%1' is not a valid integer").arg(val));
				}
			}
			else {
				r.raiseError(QCoreApplication::translate("dmarcparser", "Duplicate <%1> tag").arg(QLatin1String("count")));
			}
		}
		else if (r.name() == QLatin1String("policy_evaluated")) {
			if (!this->has_policy) {
				this->has_policy = true;
				this->evaluated_policy.d_func()->parse(r);
			}
			else {
				r.raiseError(QCoreApplication::translate("dmarcparser", "Duplicate <%1> tag").arg(QLatin1String("policy_evaluated")));
			}
		}
		else {
			r.raiseError(QCoreApplication::translate("dmarcparser", "Unexpected element <%1>").arg(r.name().toString()));
		}
	}

	if (!r.hasError()) {
		if (!seen_sourceip) {
			r.raiseError(QCoreApplication::translate("dmarcparser", "No <%1> tag").arg(QLatin1String("source_ip")));
		}
		else if (!seen_count) {
			r.raiseError(QCoreApplication::translate("dmarcparser", "No <%1> tag").arg(QLatin1String("count")));
		}
	}

	return !r.hasError();
}

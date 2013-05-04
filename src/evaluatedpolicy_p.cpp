#include <QtCore/QCoreApplication>
#include <QtCore/QXmlStreamReader>
#include "evaluatedpolicy_p.h"
#include "overridereason.h"
#include "overridereason_p.h"
#include "private.h"

DMARC::EvaluatedPolicyPrivate::EvaluatedPolicyPrivate(void)
	: QSharedData(), disposition(DMARC::DispositionUnknown), dkim(DMARC::OutcomeUnknown), spf(DMARC::OutcomeUnknown), reasons()
{
}

bool DMARC::EvaluatedPolicyPrivate::parse(QXmlStreamReader& r)
{
	bool seen_disposition = false;
	bool seen_dkim        = false;
	bool seen_spf         = false;

	while (r.readNextStartElement()) {
		if (r.name() == QLatin1String("disposition")) {
			if (!seen_disposition) {
				QString value     = r.readElementText();
				seen_disposition  = true;
				this->disposition = string2disposition(value);

				if (DMARC::DispositionUnknown == this->disposition) {
					r.raiseError(QCoreApplication::translate("dmarcparser", "Value '%1' is not valid for <%2>").arg(value, QLatin1String("disposition")));
				}
			}
			else {
				r.raiseError(QCoreApplication::translate("dmarcparser", "Duplicate <%1> tag").arg(QLatin1String("disposition")));
			}
		}
		else if (r.name() == QLatin1String("dkim")) {
			if (!seen_dkim) {
				QString value = r.readElementText();
				seen_dkim     = true;
				this->dkim    = string2outcome(value);

				if (DMARC::OutcomeUnknown == this->dkim) {
					r.raiseError(QCoreApplication::translate("dmarcparser", "Value '%1' is not valid for <%2>").arg(value, QLatin1String("dkim")));
				}
			}
			else {
				r.raiseError(QCoreApplication::translate("dmarcparser", "Duplicate <%1> tag").arg(QLatin1String("dkim")));
			}
		}
		else if (r.name() == QLatin1String("spf")) {
			if (!seen_spf) {
				QString value = r.readElementText();
				seen_spf      = true;
				this->spf     = string2outcome(value);

				if (DMARC::OutcomeUnknown == this->spf) {
					r.raiseError(QCoreApplication::translate("dmarcparser", "Value '%1' is not valid for <%2>").arg(value, QLatin1String("spf")));
				}
			}
			else {
				r.raiseError(QCoreApplication::translate("dmarcparser", "Duplicate <%1> tag").arg(QLatin1String("spf")));
			}
		}
		else if (r.name() == QLatin1String("reason")) {
			DMARC::OverrideReason reason;
			if (reason.d_func()->parse(r)) {
				this->reasons.append(reason);
			}
		}
		else {
			r.raiseError(QCoreApplication::translate("dmarcparser", "Unexpected element <%1>").arg(r.name().toString()));
		}
	}

	if (!r.hasError()) {
		if (!seen_disposition) {
			r.raiseError(QCoreApplication::translate("dmarcparser", "No <%1> tag").arg(QLatin1String("disposition")));
		}
	}

	return !r.hasError();
}

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
	while (r.readNextStartElement()) {
		if (r.name() == QLatin1String("disposition")) {
			this->disposition = string2disposition(r.readElementText());
		}
		else if (r.name() == QLatin1String("dkim")) {
			this->dkim = string2outcome(r.readElementText());
		}
		else if (r.name() == QLatin1String("spf")) {
			this->spf = string2outcome(r.readElementText());
		}
		else if (r.name() == QLatin1String("reason")) {
			DMARC::OverrideReason reason;
			if (reason.d_func()->parse(r)) {
				this->reasons.append(reason);
			}
		}
		else {
			r.raiseError(QLatin1String("Unexpected element"));
		}
	}

	return !r.hasError();
}

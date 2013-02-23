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
	while (r.readNextStartElement()) {
		if (r.name() == QLatin1String("source_ip")) {
			this->source_ip = r.readElementText();
		}
		else if (r.name() == QLatin1String("count")) {
			this->count = r.readElementText().toInt();
		}
		else if (r.name() == QLatin1String("policy_evaluated")) {
			this->has_policy = true;
			this->evaluated_policy.d_func()->parse(r);
		}
		else {
			r.raiseError(QLatin1String("Unexpected element"));
		}
	}

	return !r.hasError();
}

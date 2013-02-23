#include <QtCore/QXmlStreamReader>
#include "publishedpolicy_p.h"
#include "private.h"

DMARC::PublishedPolicyPrivate::PublishedPolicyPrivate(void)
	: QSharedData(), domain(), adkim(DMARC::UnknownPolicy), aspf(DMARC::UnknownPolicy), p(DMARC::DispositionUnknown), sp(DMARC::DispositionUnknown), pct(0)
{
}

bool DMARC::PublishedPolicyPrivate::parse(QXmlStreamReader& r)
{
	while (r.readNextStartElement()) {
		if (r.name() == QLatin1String("domain")) {
			this->domain = r.readElementText();
		}
		else if (r.name() == QLatin1String("adkim")) {
			this->adkim = string2policy(r.readElementText());
		}
		else if (r.name() == QLatin1String("aspf")) {
			this->aspf = string2policy(r.readElementText());
		}
		else if (r.name() == QLatin1String("p")) {
			this->p = string2disposition(r.readElementText());
		}
		else if (r.name() == QLatin1String("sp")) {
			this->sp = string2disposition(r.readElementText());
		}
		else if (r.name() == QLatin1String("pct")) {
			this->pct = r.readElementText().toInt();
		}
		else {
			r.raiseError(QLatin1String("Unexpected element"));
		}
	}

	return !r.hasError();
}

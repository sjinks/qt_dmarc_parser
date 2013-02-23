#include <QtCore/QXmlStreamReader>
#include "spfauthenticationresult_p.h"
#include "private.h"

DMARC::SPFAuthenticationResultPrivate::SPFAuthenticationResultPrivate(void)
	: QSharedData(), domain(), result(DMARC::SpfUnknown)
{
}

bool DMARC::SPFAuthenticationResultPrivate::parse(QXmlStreamReader& r)
{
	while (r.readNextStartElement()) {
		if (r.name() == QLatin1String("domain")) {
			this->domain = r.readElementText();
		}
		else if (r.name() == QLatin1String("result")) {
			this->result = string2spfauthres(r.readElementText());
		}
		else {
			r.raiseError(QLatin1String("Unexpected element"));
		}
	}

	return !r.hasError();
}

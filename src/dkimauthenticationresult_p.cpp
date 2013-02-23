#include <QtCore/QXmlStreamReader>
#include "dkimauthenticationresult_p.h"
#include "private.h"

DMARC::DKIMAuthenticationResultPrivate::DKIMAuthenticationResultPrivate(void)
	: QSharedData(), domain(), result(DMARC::DkimUnknown), human_result()
{
}

bool DMARC::DKIMAuthenticationResultPrivate::parse(QXmlStreamReader& r)
{
	while (r.readNextStartElement()) {
		if (r.name() == QLatin1String("domain")) {
			this->domain = r.readElementText();
		}
		else if (r.name() == QLatin1String("result")) {
			this->result = string2dkimauthres(r.readElementText());
		}
		else if (r.name() == QLatin1String("human_result")) {
			this->human_result = r.readElementText();
		}
		else {
			r.raiseError(QLatin1String("Unexpected element"));
		}
	}

	return !r.hasError();
}

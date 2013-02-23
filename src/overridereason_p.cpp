#include <QtCore/QXmlStreamReader>
#include "overridereason_p.h"
#include "private.h"

DMARC::OverrideReasonPrivate::OverrideReasonPrivate(void)
	: QSharedData(), type(DMARC::OverrideUnknown), comment()
{
}

bool DMARC::OverrideReasonPrivate::parse(QXmlStreamReader& r)
{
	while (r.readNextStartElement()) {
		if (r.name() == QLatin1String("type")) {
			this->type = string2ot(r.readElementText());
		}
		else if (r.name() == QLatin1String("comment")) {
			this->comment = r.readElementText();
		}
		else {
			r.raiseError(QLatin1String("Unexpected element"));
		}
	}

	return !r.hasError();
}

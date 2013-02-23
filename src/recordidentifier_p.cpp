#include <QtCore/QXmlStreamReader>
#include "recordidentifier_p.h"

DMARC::RecordIdentifierPrivate::RecordIdentifierPrivate(void)
	: QSharedData(), envelope_to(), header_from()
{
}

bool DMARC::RecordIdentifierPrivate::parse(QXmlStreamReader& r)
{
	while (r.readNextStartElement()) {
		if (r.name() == QLatin1String("envelope_to")) {
			this->envelope_to = r.readElementText();
		}
		else if (r.name() == QLatin1String("header_from")) {
			this->header_from = r.readElementText();
		}
		else {
			r.raiseError(QLatin1String("Unexpected element"));
		}
	}

	return !r.hasError();
}

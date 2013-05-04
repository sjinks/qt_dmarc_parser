#include <QtCore/QCoreApplication>
#include <QtCore/QXmlStreamReader>
#include "recordidentifier_p.h"

DMARC::RecordIdentifierPrivate::RecordIdentifierPrivate(void)
	: QSharedData(), envelope_to(), header_from()
{
}

bool DMARC::RecordIdentifierPrivate::parse(QXmlStreamReader& r)
{
	bool seen_envelope = false;
	bool seen_from     = false;

	while (r.readNextStartElement()) {
		if (r.name() == QLatin1String("envelope_to")) {
			if (!seen_envelope) {
				seen_envelope     = true;
				this->envelope_to = r.readElementText();
			}
			else {
				r.raiseError(QCoreApplication::translate("dmarcparser", "Duplicate <%1> tag").arg(QLatin1String("envelope_to")));
			}
		}
		else if (r.name() == QLatin1String("header_from")) {
			if (!seen_from) {
				seen_from         = true;
				this->header_from = r.readElementText();
			}
			else {
				r.raiseError(QCoreApplication::translate("dmarcparser", "Duplicate <%1> tag").arg(QLatin1String("header_from")));
			}
		}
		else {
			r.raiseError(QCoreApplication::translate("dmarcparser", "Unexpected element <%1>").arg(r.name().toString()));
		}
	}

	if (!r.hasError()) {
		if (!seen_from) {
			r.raiseError(QCoreApplication::translate("dmarcparser", "No <%1> tag").arg(QLatin1String("header_from")));
		}
	}

	return !r.hasError();
}

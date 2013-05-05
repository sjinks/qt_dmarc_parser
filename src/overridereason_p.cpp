#include <QtCore/QCoreApplication>
#include <QtCore/QXmlStreamReader>
#include "overridereason_p.h"
#include "private.h"

DMARC::OverrideReasonPrivate::OverrideReasonPrivate(void)
	: QSharedData(), type(DMARC::OverrideUnknown), comment()
{
}

bool DMARC::OverrideReasonPrivate::parse(QXmlStreamReader& r)
{
	bool seen_type    = false;
	bool seen_comment = false;

	while (r.readNextStartElement()) {
		if (r.name() == QLatin1String("type")) {
			if (!seen_type) {
				QString val = r.readElementText();
				seen_type   = true;
				this->type  = string2ot(val);

				if (DMARC::OverrideUnknown == this->type) {
					r.raiseError(QCoreApplication::translate("dmarcparser", "Value '%1' is not valid for <%2>").arg(val, QLatin1String("type")));
				}
			}
			else {
				r.raiseError(QCoreApplication::translate("dmarcparser", "Duplicate <%1> tag").arg(QLatin1String("type")));
			}
		}
		else if (r.name() == QLatin1String("comment")) {
			if (!seen_comment) {
				seen_comment  = true;
				this->comment = r.readElementText();
			}
			else {
				r.raiseError(QCoreApplication::translate("dmarcparser", "Duplicate <%1> tag").arg(QLatin1String("comment")));
			}
		}
		else {
			r.raiseError(QCoreApplication::translate("dmarcparser", "Unexpected element <%1>").arg(r.name().toString()));
		}
	}

	if (!r.hasError()) {
		if (!seen_type) {
			r.raiseError(QCoreApplication::translate("dmarcparser", "No <%1> tag").arg(QLatin1String("type")));
		}
	}

	return !r.hasError();
}

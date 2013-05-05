#include <QtCore/QCoreApplication>
#include <QtCore/QXmlStreamReader>
#include "dkimauthenticationresult_p.h"
#include "private.h"

DMARC::DKIMAuthenticationResultPrivate::DKIMAuthenticationResultPrivate(void)
	: QSharedData(), domain(), result(DMARC::DkimUnknown), human_result()
{
}

bool DMARC::DKIMAuthenticationResultPrivate::parse(QXmlStreamReader& r)
{
	bool seen_domain = false;
	bool seen_result = false;
	bool seen_human  = false;

	while (r.readNextStartElement()) {
		if (r.name() == QLatin1String("domain")) {
			if (!seen_domain) {
				seen_domain  = true;
				this->domain = r.readElementText();
			}
			else {
				r.raiseError(QCoreApplication::translate("dmarcparser", "Duplicate <%1> tag").arg(QLatin1String("domain")));
			}
		}
		else if (r.name() == QLatin1String("result")) {
			if (!seen_result) {
				QString val  = r.readElementText();
				seen_result  = true;
				this->result = string2dkimauthres(val);

				if (DMARC::DkimUnknown == this->result) {
					r.raiseError(QCoreApplication::translate("dmarcparser", "Value '%1' is not valid for <%2>").arg(val, QLatin1String("result")));
				}
			}
			else {
				r.raiseError(QCoreApplication::translate("dmarcparser", "Duplicate <%1> tag").arg(QLatin1String("result")));
			}
		}
		else if (r.name() == QLatin1String("human_result")) {
			if (!seen_human) {
				seen_human         = true;
				this->human_result = r.readElementText();
			}
			else {
				r.raiseError(QCoreApplication::translate("dmarcparser", "Duplicate <%1> tag").arg(QLatin1String("human_result")));
			}
		}
		else {
			r.raiseError(QCoreApplication::translate("dmarcparser", "Unexpected element <%1>").arg(r.name().toString()));
		}
	}

	if (!r.hasError()) {
		if (!seen_domain) {
			r.raiseError(QCoreApplication::translate("dmarcparser", "No <%1> tag").arg(QLatin1String("domain")));
		}
		else if (!seen_result) {
			r.raiseError(QCoreApplication::translate("dmarcparser", "No <%1> tag").arg(QLatin1String("result")));
		}
	}

	return !r.hasError();
}

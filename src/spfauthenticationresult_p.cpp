#include <QtCore/QCoreApplication>
#include <QtCore/QXmlStreamReader>
#include "spfauthenticationresult_p.h"
#include "private.h"

DMARC::SPFAuthenticationResultPrivate::SPFAuthenticationResultPrivate(void)
	: QSharedData(), domain(), result(DMARC::SpfUnknown)
{
}

bool DMARC::SPFAuthenticationResultPrivate::parse(QXmlStreamReader& r)
{
	bool seen_domain = false;
	bool seen_result = false;

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
				QString value = r.readElementText();
				seen_result   = true;
				this->result  = string2spfauthres(value);
				if (DMARC::SpfUnknown == this->result) {
					r.raiseError(QCoreApplication::translate("dmarcparser", "Value '%1' is not valid for <%2>").arg(value, QLatin1String("result")));
				}
			}
			else {
				r.raiseError(QCoreApplication::translate("dmarcparser", "Duplicate <%1> tag").arg(QLatin1String("result")));
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

#include <QtCore/QCoreApplication>
#include <QtCore/QXmlStreamReader>
#include "authenticationresults_p.h"
#include "dkimauthenticationresult.h"
#include "dkimauthenticationresult_p.h"
#include "spfauthenticationresult.h"
#include "spfauthenticationresult_p.h"

DMARC::AuthenticationResultsPrivate::AuthenticationResultsPrivate(void)
	: QSharedData(), dkim(), spf()
{
}

bool DMARC::AuthenticationResultsPrivate::parse(QXmlStreamReader& r)
{
	while (r.readNextStartElement()) {
		if (r.name() == QLatin1String("spf")) {
			DMARC::SPFAuthenticationResult res;
			if (res.d_func()->parse(r)) {
				this->spf.append(res);
			}
		}
		else if (r.name() == QLatin1String("dkim")) {
			DMARC::DKIMAuthenticationResult res;
			if (res.d_func()->parse(r)) {
				this->dkim.append(res);
			}
		}
		else {
			r.raiseError(QCoreApplication::translate("dmarcparser", "Unexpected element <%1>").arg(r.name().toString()));
		}
	}

	return !r.hasError();
}

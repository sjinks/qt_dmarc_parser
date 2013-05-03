#include <QtCore/QCoreApplication>
#include <QtCore/QXmlStreamReader>
#include "record_p.h"
#include "recordrow.h"
#include "recordrow_p.h"
#include "recordidentifier_p.h"
#include "authenticationresults_p.h"

DMARC::RecordPrivate::RecordPrivate(void)
	: QSharedData(), row(), identifiers(), auth_results()
{
}

bool DMARC::RecordPrivate::parse(QXmlStreamReader& r)
{
	bool seen_row         = false;
	bool seen_identifiers = false;
	bool seen_authresults = false;

	while (r.readNextStartElement()) {
		if (r.name() == QLatin1String("row")) {
			if (!seen_row) {
				seen_row = true;
				this->row.d_func()->parse(r);
			}
			else {
				r.raiseError(QCoreApplication::translate("dmarcparser", "Duplicate <%1> tag").arg(QLatin1String("row")));
			}
		}
		else if (r.name() == QLatin1String("identifiers")) {
			if (!seen_identifiers) {
				seen_identifiers = true;
				this->identifiers.d_func()->parse(r);
			}
			else {
				r.raiseError(QCoreApplication::translate("dmarcparser", "Duplicate <%1> tag").arg(QLatin1String("identifiers")));
			}
		}
		else if (r.name() == QLatin1String("auth_results")) {
			if (!seen_authresults) {
				seen_authresults = true;
				this->auth_results.d_func()->parse(r);
			}
			else {
				r.raiseError(QCoreApplication::translate("dmarcparser", "Duplicate <%1> tag").arg(QLatin1String("auth_results")));
			}
		}
		else {
			r.raiseError(QCoreApplication::translate("dmarcparser", "Unexpected element <%1>").arg(r.name().toString()));
		}
	}

	if (!r.hasError()) {
		if (!seen_row) {
			r.raiseError(QCoreApplication::translate("dmarcparser", "No <%1> tag").arg(QLatin1String("row")));
		}
		else if (!seen_identifiers) {
			r.raiseError(QCoreApplication::translate("dmarcparser", "No <%1> tag").arg(QLatin1String("identifiers")));
		}
		else if (!seen_authresults) {
			r.raiseError(QCoreApplication::translate("dmarcparser", "No <%1> tag").arg(QLatin1String("auth_results")));
		}
	}

	return !r.hasError();
}

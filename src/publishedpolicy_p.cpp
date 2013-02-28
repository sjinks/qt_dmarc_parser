#include <QtCore/QCoreApplication>
#include <QtCore/QXmlStreamReader>
#include "publishedpolicy_p.h"
#include "private.h"

DMARC::PublishedPolicyPrivate::PublishedPolicyPrivate(void)
	: QSharedData(), domain(), adkim(DMARC::UnknownPolicy), aspf(DMARC::UnknownPolicy), p(DMARC::DispositionUnknown), sp(DMARC::DispositionUnknown), pct(0)
{
}

bool DMARC::PublishedPolicyPrivate::parse(QXmlStreamReader& r)
{
	bool seen_domain = false;
	bool seen_adkim  = false;
	bool seen_aspf   = false;
	bool seen_p      = false;
	bool seen_sp     = false;
	bool seen_pct    = false;

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
		else if (r.name() == QLatin1String("adkim")) {
			if (!seen_adkim) {
				seen_adkim    = true;
				QString value = r.readElementText();
				this->adkim   = string2policy(value);

				if (DMARC::UnknownPolicy == this->adkim) {
					r.raiseError(QCoreApplication::translate("dmarcparser", "Value '%1' is not valid for <%2>").arg(value, QLatin1String("adkim")));
				}
			}
			else {
				r.raiseError(QCoreApplication::translate("dmarcparser", "Duplicate <%1> tag").arg(QLatin1String("adkim")));
			}
		}
		else if (r.name() == QLatin1String("aspf")) {
			if (!seen_aspf) {
				seen_aspf     = true;
				QString value = r.readElementText();
				this->aspf    = string2policy(value);

				if (DMARC::UnknownPolicy == this->aspf) {
					r.raiseError(QCoreApplication::translate("dmarcparser", "Value '%1' is not valid for <%2>").arg(value, QLatin1String("aspf")));
				}
			}
			else {
				r.raiseError(QCoreApplication::translate("dmarcparser", "Duplicate <%1> tag").arg(QLatin1String("aspf")));
			}
		}
		else if (r.name() == QLatin1String("p")) {
			if (!seen_p) {
				seen_p        = true;
				QString value = r.readElementText();
				this->p       = string2disposition(value);

				if (DMARC::DispositionUnknown == this->p) {
					r.raiseError(QCoreApplication::translate("dmarcparser", "Value '%1' is not valid for <%2>").arg(value, QLatin1String("p")));
				}
			}
			else {
				r.raiseError(QCoreApplication::translate("dmarcparser", "Duplicate <%1> tag").arg(QLatin1String("p")));
			}
		}
		else if (r.name() == QLatin1String("sp")) {
			if (!seen_sp) {
				seen_sp       = true;
				QString value = r.readElementText();
				this->sp      = string2disposition(value);

				if (DMARC::DispositionUnknown == this->sp) {
					r.raiseError(QCoreApplication::translate("dmarcparser", "Value '%1' is not valid for <%2>").arg(value, QLatin1String("sp")));
				}
			}
			else {
				r.raiseError(QCoreApplication::translate("dmarcparser", "Duplicate <%1> tag").arg(QLatin1String("sp")));
			}
		}
		else if (r.name() == QLatin1String("pct")) {
			if (!seen_pct) {
				bool ok;
				seen_pct      = true;
				QString value = r.readElementText();
				this->pct     = value.toInt(&ok);

				if (!ok) {
					r.raiseError(QCoreApplication::translate("dmarcparser", "Value '%1' is not a valid integer").arg(value));
				}
			}
			else {
				r.raiseError(QCoreApplication::translate("dmarcparser", "Duplicate <%1> tag").arg(QLatin1String("pct")));
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
		else if (!seen_adkim) {
			r.raiseError(QCoreApplication::translate("dmarcparser", "No <%1> tag").arg(QLatin1String("adkim")));
		}
		else if (!seen_aspf) {
			r.raiseError(QCoreApplication::translate("dmarcparser", "No <%1> tag").arg(QLatin1String("aspf")));
		}
		else if (!seen_p) {
			r.raiseError(QCoreApplication::translate("dmarcparser", "No <%1> tag").arg(QLatin1String("p")));
		}
		else if (!seen_pct) {
			r.raiseError(QCoreApplication::translate("dmarcparser", "No <%1> tag").arg(QLatin1String("pct")));
		}
	}

	return !r.hasError();
}

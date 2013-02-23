#include <QtCore/QXmlStreamReader>
#include "record_p.h"
#include "recordrow.h"
#include "recordrow_p.h"
#include "recordidentifier_p.h"
#include "authenticationresults_p.h"

DMARC::RecordPrivate::RecordPrivate(void)
	: QSharedData(), rows(), identifiers(), auth_results()
{
}

bool DMARC::RecordPrivate::parse(QXmlStreamReader& r)
{
	while (r.readNextStartElement()) {
		if (r.name() == QLatin1String("row")) {
			DMARC::RecordRow rec;
			if (rec.d_func()->parse(r)) {
				this->rows.append(rec);
			}
		}
		else if (r.name() == QLatin1String("identifiers")) {
			this->identifiers.d_func()->parse(r);
		}
		else if (r.name() == QLatin1String("auth_results")) {
			this->auth_results.d_func()->parse(r);
		}
		else {
			r.raiseError(QLatin1String("Unexpected element"));
		}
	}

	return !r.hasError();
}

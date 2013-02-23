#include <QtCore/QXmlStreamReader>
#include "reportmetadata_p.h"

DMARC::ReportMetadataPrivate::ReportMetadataPrivate(void)
	: QSharedData(), org_name(), email(), extra_contact_info(), report_id(), date_range(), errors()
{
}

bool DMARC::ReportMetadataPrivate::parse(QXmlStreamReader& r)
{
	while (r.readNextStartElement()) {
		if (r.name() == QLatin1String("org_name")) {
			this->org_name = r.readElementText();
		}
		else if (r.name() == QLatin1String("email")) {
			this->email = r.readElementText();
		}
		else if (r.name() == QLatin1String("extra_contact_info")) {
			this->extra_contact_info = r.readElementText();
		}
		else if (r.name() == QLatin1String("report_id")) {
			this->report_id = r.readElementText();
		}
		else if (r.name() == QLatin1String("date_range")) {
			while (r.readNextStartElement()) {
				if (r.name() == QLatin1String("begin")) {
					this->date_range.first = r.readElementText().toULongLong();
				}
				else if (r.name() == QLatin1String("end")) {
					this->date_range.second = r.readElementText().toULongLong();
				}
				else {
					r.raiseError(QLatin1String("Unexpected element"));
				}
			}
		}
		else if (r.name() == QLatin1String("error")) {
			this->errors.append(r.readElementText());
		}
		else {
			r.raiseError(QLatin1String("Unexpected element"));
		}
	}

	return !r.hasError();
}

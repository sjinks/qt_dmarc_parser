#include <QtCore/QCoreApplication>
#include <QtCore/QXmlStreamReader>
#include "reportmetadata_p.h"

DMARC::ReportMetadataPrivate::ReportMetadataPrivate(void)
	: QSharedData(), org_name(), email(), extra_contact_info(), report_id(), date_range(), errors()
{
}

bool DMARC::ReportMetadataPrivate::parse(QXmlStreamReader& r)
{
	bool seen_orgname = false;
	bool seen_email   = false;
	bool seen_eci     = false;
	bool seen_rid     = false;
	bool seen_date    = false;

	while (r.readNextStartElement()) {
		if (r.name() == QLatin1String("org_name")) {
			if (!seen_orgname) {
				seen_orgname   = true;
				this->org_name = r.readElementText();
			}
			else {
				r.raiseError(QCoreApplication::translate("dmarcparser", "Duplicate <%1> tag").arg(QLatin1String("org_name")));
			}
		}
		else if (r.name() == QLatin1String("email")) {
			if (!seen_email) {
				seen_email  = true;
				this->email = r.readElementText();
			}
			else {
				r.raiseError(QCoreApplication::translate("dmarcparser", "Duplicate <%1> tag").arg(QLatin1String("email")));
			}
		}
		else if (r.name() == QLatin1String("extra_contact_info")) {
			if (!seen_eci) {
				seen_eci                 = true;
				this->extra_contact_info = r.readElementText();
			}
			else {
				r.raiseError(QCoreApplication::translate("dmarcparser", "Duplicate <%1> tag").arg(QLatin1String("extra_contact_info")));
			}
		}
		else if (r.name() == QLatin1String("report_id")) {
			if (!seen_rid) {
				seen_rid        = true;
				this->report_id = r.readElementText();
			}
			else {
				r.raiseError(QCoreApplication::translate("dmarcparser", "Duplicate <%1> tag").arg(QLatin1String("report_id")));
			}
		}
		else if (r.name() == QLatin1String("date_range")) {
			if (!seen_date) {
				seen_date       = true;
				bool seen_begin = false;
				bool seen_end   = false;
				bool ok;

				while (r.readNextStartElement()) {
					if (r.name() == QLatin1String("begin")) {
						if (!seen_begin) {
							seen_begin             = true;
							QString value          = r.readElementText();
							this->date_range.first = value.toULongLong(&ok);

							if (!ok) {
								r.raiseError(QCoreApplication::translate("dmarcparser", "Value '%1' is not a valid integer").arg(value));
							}
						}
						else {
							r.raiseError(QCoreApplication::translate("dmarcparser", "Duplicate <%1> tag").arg(QLatin1String("begin")));
						}
					}
					else if (r.name() == QLatin1String("end")) {
						if (!seen_end) {
							seen_end                = true;
							QString value           = r.readElementText();
							this->date_range.second = value.toULongLong(&ok);

							if (!ok) {
								r.raiseError(QCoreApplication::translate("dmarcparser", "Value '%1' is not a valid integer").arg(value));
							}
						}
						else {
							r.raiseError(QCoreApplication::translate("dmarcparser", "Duplicate <%1> tag").arg(QLatin1String("end")));
						}
					}
					else {
						r.raiseError(QCoreApplication::translate("dmarcparser", "Unexpected element <%1>").arg(r.name().toString()));
					}
				}

				if (!seen_begin) {
					r.raiseError(QCoreApplication::translate("dmarcparser", "No <%1> tag").arg(QLatin1String("begin")));
				}
				else if (!seen_end) {
					r.raiseError(QCoreApplication::translate("dmarcparser", "No <%1> tag").arg(QLatin1String("end")));
				}
			}
			else {
				r.raiseError(QCoreApplication::translate("dmarcparser", "Duplicate <%1> tag").arg(QLatin1String("date_range")));
			}
		}
		else if (r.name() == QLatin1String("error")) {
			this->errors.append(r.readElementText());
		}
		else {
			r.raiseError(QCoreApplication::translate("dmarcparser", "Unexpected element <%1>").arg(r.name().toString()));
		}
	}

	if (!r.hasError()) {
		if (!seen_orgname) {
			r.raiseError(QCoreApplication::translate("dmarcparser", "No <%1> tag").arg(QLatin1String("org_name")));
		}
		else if (!seen_email) {
			r.raiseError(QCoreApplication::translate("dmarcparser", "No <%1> tag").arg(QLatin1String("email")));
		}
		else if (!seen_rid) {
			r.raiseError(QCoreApplication::translate("dmarcparser", "No <%1> tag").arg(QLatin1String("report_id")));
		}
		else if (!seen_date) {
			r.raiseError(QCoreApplication::translate("dmarcparser", "No <%1> tag").arg(QLatin1String("date_range")));
		}
	}

	return !r.hasError();
}

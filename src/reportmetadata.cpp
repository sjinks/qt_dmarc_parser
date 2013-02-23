#include "reportmetadata.h"
#include "reportmetadata_p.h"

DMARC::ReportMetadata::ReportMetadata(void)
	: d_ptr(new DMARC::ReportMetadataPrivate())
{
}

DMARC::ReportMetadata::~ReportMetadata(void)
{
}

QString DMARC::ReportMetadata::orgName(void) const
{
	Q_D(const DMARC::ReportMetadata);
	return d->org_name;
}

QString DMARC::ReportMetadata::email(void) const
{
	Q_D(const DMARC::ReportMetadata);
	return d->email;
}

QString DMARC::ReportMetadata::extraContactInfo(void) const
{
	Q_D(const DMARC::ReportMetadata);
	return d->extra_contact_info;
}

QString DMARC::ReportMetadata::reportID(void) const
{
	Q_D(const DMARC::ReportMetadata);
	return d->report_id;
}

const QPair<qulonglong, qulonglong>& DMARC::ReportMetadata::dateRange(void) const
{
	Q_D(const DMARC::ReportMetadata);
	return d->date_range;
}

const QStringList& DMARC::ReportMetadata::errors(void) const
{
	Q_D(const DMARC::ReportMetadata);
	return d->errors;
}

#ifndef DMARC_REPORTMETADATA_P_H
#define DMARC_REPORTMETADATA_P_H

#include <QtCore/QtGlobal>
#include <QtCore/QPair>
#include <QtCore/QSharedData>
#include <QtCore/QStringList>

QT_FORWARD_DECLARE_CLASS(QXmlStreamReader)

namespace DMARC {

class Q_DECL_HIDDEN ReportMetadataPrivate : public QSharedData {
public:
	ReportMetadataPrivate(void);
	bool parse(QXmlStreamReader& r);

	QString org_name;
	QString email;
	QString extra_contact_info;
	QString report_id;
	QPair<qulonglong, qulonglong> date_range;
	QStringList errors;
};

} // namespace DMARC

#endif // DMARC_REPORTMETADATA_P_H

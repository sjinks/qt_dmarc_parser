#ifndef DMARC_RECORDIDENTIFIER_P_H
#define DMARC_RECORDIDENTIFIER_P_H

#include <QtCore/QSharedData>
#include <QtCore/QString>
#include "dmarcparser.h"

QT_FORWARD_DECLARE_CLASS(QXmlStreamReader)

namespace DMARC {

class Q_DECL_HIDDEN RecordIdentifierPrivate : public QSharedData {
public:
	RecordIdentifierPrivate(void);
	bool parse(QXmlStreamReader& r);

	QString envelope_to;
	QString header_from;
};

} // namespace DMARC

#endif // DMARC_RECORDIDENTIFIER_P_H

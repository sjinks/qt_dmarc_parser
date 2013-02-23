#ifndef DMARC_OVERRIDEREASON_P_H
#define DMARC_OVERRIDEREASON_P_H

#include <QtCore/QSharedData>
#include <QtCore/QString>
#include "dmarcparser.h"

QT_FORWARD_DECLARE_CLASS(QXmlStreamReader)

namespace DMARC {

class Q_DECL_HIDDEN OverrideReasonPrivate : public QSharedData {
public:
	OverrideReasonPrivate(void);
	bool parse(QXmlStreamReader& r);

	DMARC::OverrideType type;
	QString comment;
};

} // namespace DMARC

#endif // DMARC_OVERRIDEREASON_P_H

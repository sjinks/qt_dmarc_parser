#ifndef DMARC_PUBLISHEDPOLICY_P_H
#define DMARC_PUBLISHEDPOLICY_P_H

#include <QtCore/QSharedData>
#include <QtCore/QString>
#include "dmarcparser.h"

QT_FORWARD_DECLARE_CLASS(QXmlStreamReader)

namespace DMARC {

class Q_DECL_HIDDEN PublishedPolicyPrivate : public QSharedData {
public:
	PublishedPolicyPrivate(void);
	bool parse(QXmlStreamReader& r);

	QString domain;
	DMARC::Policy adkim;
	DMARC::Policy aspf;
	DMARC::Disposition p;
	DMARC::Disposition sp;
	int pct;
};

} // namespace DMARC

#endif // DMARC_PUBLISHEDPOLICY_P_H

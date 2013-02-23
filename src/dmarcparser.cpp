#include <QtCore/QScopedPointer>
#include <QtCore/QXmlStreamReader>
#include "dmarcparser.h"
#include "feedback.h"
#include "feedback_p.h"

namespace DMARC {

class Q_DECL_HIDDEN ReportParser {
public:
	ReportParser(const QString& report) : m_reader(report) {}
	ReportParser(const QByteArray& report) : m_reader(report) {}
	ReportParser(QIODevice* report) : m_reader(report) {}

	DMARC::Feedback* parse(QString* error)
	{
		QScopedPointer<DMARC::Feedback> result(new DMARC::Feedback());

		if (this->m_reader.readNextStartElement() && this->m_reader.name() == QLatin1String("feedback")) {
			if (result->d_func()->parse(this->m_reader)) {
				Q_ASSERT(!this->m_reader.hasError());
				if (error) {
					error->clear();
				}

				return result.take();
			}
		}
		else {
			this->m_reader.raiseError(QLatin1String("Not a DMARC report"));
		}

		Q_ASSERT(this->m_reader.hasError());
		if (error) {
			*error = this->m_reader.errorString();
		}

		return 0;
	}

private:
	QXmlStreamReader m_reader;
};

}

DMARC::Feedback* DMARC::parseReport(const QString& report, QString* error)
{
	DMARC::ReportParser parser(report);
	return parser.parse(error);
}

DMARC::Feedback* DMARC::parseReport(const QByteArray& report, QString* error)
{
	DMARC::ReportParser parser(report);
	return parser.parse(error);
}

DMARC::Feedback* DMARC::parseReport(QIODevice* report, QString* error)
{
	DMARC::ReportParser parser(report);
	return parser.parse(error);
}

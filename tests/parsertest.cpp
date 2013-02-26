#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QScopedPointer>
#include <QtTest/QTest>
#include <QtXmlPatterns/QXmlSchema>
#include <QtXmlPatterns/QXmlSchemaValidator>
#include "dmarcparser.h"
#include "feedback.h"

class ParserTest : public QObject {
	Q_OBJECT
public:

private:
	QXmlSchema m_schema;
	QXmlSchemaValidator m_validator;

private Q_SLOTS:
	void initTestCase(void)
	{
		QVERIFY(this->m_schema.load(QUrl::fromEncoded("qrc:/data/dmarc.xsd")));
		QVERIFY(this->m_schema.isValid());
		this->m_validator.setSchema(this->m_schema);
	}

	void basicTestRealData(void)
	{
		QFETCH(QByteArray, data);
		QFETCH(bool, valid);

		QString error;
		QScopedPointer<DMARC::Feedback> res(DMARC::parseReport(data, &error));
		if (valid) {
			QVERIFY(!res.isNull());
			QVERIFY(error.isEmpty());
			QVERIFY(this->m_validator.validate(data));
		}
		else {
			QVERIFY(res.isNull());
			QVERIFY(!this->m_validator.validate(data));
		}
	}

	void basicTestRealData_data(void)
	{
		QTest::addColumn<QByteArray>("data");
		QTest::addColumn<bool>("valid");

		QStringList files;
		files
			<< QLatin1String("real-aol-1")
			<< QLatin1String("real-google-1")
			<< QLatin1String("real-google-2")
			<< QLatin1String("real-google-3")
			<< QLatin1String("real-hotmail-1")
			<< QLatin1String("real-hotmail-2")
			<< QLatin1String("real-mail.ru-1")
			<< QLatin1String("real-yahoo-1")
			<< QLatin1String("real-yahoo-2")
			<< QLatin1String("minimum")
		;

		for (int i=0; i<files.size(); ++i) {
			QFile file(QLatin1String(":/data/real/") + files.at(i) + QLatin1String(".xml"));
			QVERIFY(file.open(QIODevice::ReadOnly));
			QTest::newRow(files.at(i).toLatin1().constData()) << file.readAll() << true;
		}
	}
};

#include "parsertest.moc"

int main(int argc, char** argv)
{
	QCoreApplication app(argc, argv);
	ParserTest test;
	return QTest::qExec(&test, argc, argv);
}

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QScopedPointer>
#include <QtTest/QTest>
#include <QtXmlPatterns/QAbstractMessageHandler>
#include <QtXmlPatterns/QXmlSchema>
#include <QtXmlPatterns/QXmlSchemaValidator>
#include "dmarcparser.h"
#include "feedback.h"

class MyMessageHandler : public QAbstractMessageHandler {
	Q_OBJECT
public:
	explicit MyMessageHandler(QObject* parent = 0) : QAbstractMessageHandler(parent) {}

protected:
	virtual void handleMessage(QtMsgType type, const QString& description, const QUrl& identifier, const QSourceLocation& sourceLocation)
	{
		Q_UNUSED(type)
		Q_UNUSED(description)
		Q_UNUSED(identifier)
		Q_UNUSED(sourceLocation)
	}

};

class ParserTest : public QObject {
	Q_OBJECT
public:
	explicit ParserTest(QObject* parent = 0)
		: QObject(parent), m_handler(new MyMessageHandler(this))
	{
	}

private:
	MyMessageHandler* m_handler;
	QXmlSchema m_schema;
	QXmlSchema m_official_schema;
	QXmlSchemaValidator m_validator;
	QXmlSchemaValidator m_official_validator;

private Q_SLOTS:
	void initTestCase(void)
	{
		QVERIFY(this->m_schema.load(QUrl::fromEncoded("qrc:/data/dmarc.xsd")));
		QVERIFY(this->m_schema.isValid());
		this->m_validator.setSchema(this->m_schema);

		QVERIFY(this->m_official_schema.load(QUrl::fromEncoded("qrc:/data/rua.xsd")));
		QVERIFY(this->m_official_schema.isValid());
		this->m_official_validator.setSchema(this->m_official_schema);

		this->m_validator.setMessageHandler(this->m_handler);
		this->m_official_validator.setMessageHandler(this->m_handler);
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
			<< QLatin1String("real-aol-2")
			<< QLatin1String("real-google-1")
			<< QLatin1String("real-google-2")
			<< QLatin1String("real-google-3")
			<< QLatin1String("real-hotmail-1")
			<< QLatin1String("real-hotmail-2")
			<< QLatin1String("real-mail.ru-1")
			<< QLatin1String("real-yahoo-1")
			<< QLatin1String("real-yahoo-2")
		;

		for (int i=0; i<files.size(); ++i) {
			QFile file(QLatin1String(":/data/real/") + files.at(i) + QLatin1String(".xml"));
			QVERIFY(file.open(QIODevice::ReadOnly));
			QTest::newRow(files.at(i).toLatin1().constData()) << file.readAll() << true;
		}
	}

	void schemaTest(void)
	{
		QFETCH(QByteArray, data);
		QFETCH(bool, valid);

		if (valid) {
			QVERIFY(this->m_validator.validate(data));
			QVERIFY(this->m_official_validator.validate(data));
		}
		else {
			QVERIFY(!this->m_validator.validate(data));
			QVERIFY(!this->m_official_validator.validate(data));
		}
	}

	void schemaTest_data(void)
	{
		QTest::addColumn<QByteArray>("data");
		QTest::addColumn<bool>("valid");

		QStringList files;
		files
			<< QLatin1String("invalid-dkim-spf-seq")
			<< QLatin1String("invalid-dup-email")
			<< QLatin1String("invalid-dup-row")
			<< QLatin1String("invalid-feedback-seq")
			<< QLatin1String("invalid-no-meta")
			<< QLatin1String("invalid-no-policy")
			<< QLatin1String("invalid-no-records")
			<< QLatin1String("invalid-spf-dkim-seq")
			<< QLatin1String("valid-all")
			<< QLatin1String("valid-min")
		;

		for (int i=0; i<files.size(); ++i) {
			QFile file(QLatin1String(":/data/schema/") + files.at(i) + QLatin1String(".xml"));
			QVERIFY(file.open(QIODevice::ReadOnly));
			QTest::newRow(files.at(i).toLatin1().constData()) << file.readAll() << files.at(i).startsWith(QLatin1String("valid-"));
		}
	}

	void feedbackTest(void)
	{
		QFETCH(QByteArray, data);
		QFETCH(QString, error);

		QString e;
		QScopedPointer<DMARC::Feedback> res(DMARC::parseReport(data, &e));

		QVERIFY(res.isNull());
		QVERIFY(!this->m_validator.validate(data));
		QCOMPARE(e, error);
	}

	void feedbackTest_data(void)
	{
		QTest::addColumn<QByteArray>("data");
		QTest::addColumn<QString>("error");

		QStringList files;
		files
			<< QLatin1String("invalid-no-meta")       << QCoreApplication::translate("dmarcparser", "No <%1> tag").arg(QLatin1String("report_metadata"))
			<< QLatin1String("invalid-no-policy")     << QCoreApplication::translate("dmarcparser", "No <%1> tag").arg(QLatin1String("policy_published"))
			<< QLatin1String("invalid-no-records")    << QCoreApplication::translate("dmarcparser", "No <%1> tag").arg(QLatin1String("record"))
			<< QLatin1String("invalid-two-meta")      << QCoreApplication::translate("dmarcparser", "Duplicate <%1> tag").arg(QLatin1String("report_metadata"))
			<< QLatin1String("invalid-two-policies")  << QCoreApplication::translate("dmarcparser", "Duplicate <%1> tag").arg(QLatin1String("policy_published"))
			<< QLatin1String("invalid-unexpected")    << QCoreApplication::translate("dmarcparser", "Unexpected element <%1>").arg(QLatin1String("unexpected-element"))
		;

		QCOMPARE(files.size() % 2, 0);

		for (int i=0; i<files.size(); i+=2) {
			QString fname = files.at(i);
			QString error = files.at(i+1);

			QFile file(QLatin1String(":/data/feedback/") + fname + QLatin1String(".xml"));
			QVERIFY(file.open(QIODevice::ReadOnly));

			QTest::newRow(fname.toLatin1().constData()) << file.readAll() << error;
		}
	}

	void metadataTest(void)
	{
		QFETCH(QByteArray, data);
		QFETCH(QString, error);

		QString e;
		QScopedPointer<DMARC::Feedback> res(DMARC::parseReport(data, &e));

		QVERIFY(res.isNull());
		QVERIFY(!this->m_validator.validate(data));
		QCOMPARE(e, error);
	}

	void metadataTest_data(void)
	{
		QTest::addColumn<QByteArray>("data");
		QTest::addColumn<QString>("error");

		QStringList files;
		files
			<< QLatin1String("invalid-dr-begin")       << QCoreApplication::translate("dmarcparser", "Value '%1' is not a valid integer").arg(QLatin1String("string"))
			<< QLatin1String("invalid-dr-end")         << QCoreApplication::translate("dmarcparser", "Value '%1' is not a valid integer").arg(QLatin1String("string"))
			<< QLatin1String("invalid-dr-extra")       << QCoreApplication::translate("dmarcparser", "Unexpected element <%1>").arg(QLatin1String("extra"))
			<< QLatin1String("invalid-dr-no-begin")    << QCoreApplication::translate("dmarcparser", "No <%1> tag").arg(QLatin1String("begin"))
			<< QLatin1String("invalid-dr-no-end")      << QCoreApplication::translate("dmarcparser", "No <%1> tag").arg(QLatin1String("end"))
			<< QLatin1String("invalid-dr-two-begins")  << QCoreApplication::translate("dmarcparser", "Duplicate <%1> tag").arg(QLatin1String("begin"))
			<< QLatin1String("invalid-dr-two-ends")    << QCoreApplication::translate("dmarcparser", "Duplicate <%1> tag").arg(QLatin1String("end"))
			<< QLatin1String("invalid-extra")          << QCoreApplication::translate("dmarcparser", "Unexpected element <%1>").arg(QLatin1String("extra"))
			<< QLatin1String("invalid-no-daterange")   << QCoreApplication::translate("dmarcparser", "No <%1> tag").arg(QLatin1String("date_range"))
			<< QLatin1String("invalid-no-email")       << QCoreApplication::translate("dmarcparser", "No <%1> tag").arg(QLatin1String("email"))
			<< QLatin1String("invalid-no-orgname")     << QCoreApplication::translate("dmarcparser", "No <%1> tag").arg(QLatin1String("org_name"))
			<< QLatin1String("invalid-no-reportid")    << QCoreApplication::translate("dmarcparser", "No <%1> tag").arg(QLatin1String("report_id"))
			<< QLatin1String("invalid-two-dateranges") << QCoreApplication::translate("dmarcparser", "Duplicate <%1> tag").arg(QLatin1String("date_range"))
			<< QLatin1String("invalid-two-ecis")       << QCoreApplication::translate("dmarcparser", "Duplicate <%1> tag").arg(QLatin1String("extra_contact_info"))
			<< QLatin1String("invalid-two-emails")     << QCoreApplication::translate("dmarcparser", "Duplicate <%1> tag").arg(QLatin1String("email"))
			<< QLatin1String("invalid-two-orgnames")   << QCoreApplication::translate("dmarcparser", "Duplicate <%1> tag").arg(QLatin1String("org_name"))
			<< QLatin1String("invalid-two-reportids")  << QCoreApplication::translate("dmarcparser", "Duplicate <%1> tag").arg(QLatin1String("report_id"))
		;

		QCOMPARE(files.size() % 2, 0);

		for (int i=0; i<files.size(); i+=2) {
			QString fname = files.at(i);
			QString error = files.at(i+1);

			QFile file(QLatin1String(":/data/metadata/") + fname + QLatin1String(".xml"));
			QVERIFY(file.open(QIODevice::ReadOnly));

			QTest::newRow(fname.toLatin1().constData()) << file.readAll() << error;
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

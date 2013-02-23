#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QScopedPointer>
#include <QtTest/QTest>
#include "dmarcparser.h"
#include "feedback.h"

class ParserTest : public QObject {
	Q_OBJECT
public:

private Q_SLOTS:
	void basicTestRealData(void)
	{
		QFETCH(QByteArray, data);
		QFETCH(bool, valid);

		QString error;
		QScopedPointer<DMARC::Feedback> res(DMARC::parseReport(data, &error));
		if (valid) {
			QVERIFY(!res.isNull());
			QVERIFY(error.isEmpty());
		}
		else {
			QVERIFY(res.isNull());
		}
	}

	void basicTestRealData_data(void)
	{
		QTest::addColumn<QByteArray>("data");
		QTest::addColumn<bool>("valid");

		QStringList files;
		files
			<< QLatin1String("real-google-1")
			<< QLatin1String("real-google-2")
			<< QLatin1String("real-google-3")
			<< QLatin1String("real-hotmail-1")
			<< QLatin1String("real-hotmail-2")
			<< QLatin1String("real-yahoo-1")
			<< QLatin1String("real-yahoo-2")
		;

		for (int i=0; i<files.size(); ++i) {
			QFile file(QLatin1String(":/data/") + files.at(i) + QLatin1String(".xml"));
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

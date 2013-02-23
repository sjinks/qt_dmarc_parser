#ifndef DMARCPARSER_H
#define DMARCPARSER_H

#include <QtCore/QtGlobal>

#if defined(DMARCPARSER_LIBRARY)
#	define DMARCPARSERSHARED_EXPORT Q_DECL_EXPORT
#else
#	define DMARCPARSERSHARED_EXPORT Q_DECL_IMPORT
#endif

QT_FORWARD_DECLARE_CLASS(QIODevice)

namespace DMARC {

enum Policy {
	UnknownPolicy,
	RelaxedPolicy,
	StrictPolicy
};

enum Disposition {
	DispositionUnknown,
	DispositionNone,
	DispositionReject,
	DispositionQuarantine
};

enum OverrideType {
	OverrideUnknown,
	OverrideForwarded,
	OverrideSampledOut,
	OverrideTrustedForwarder,
	OverrideMailingList,
	OverrideLocalPolicy,
	OverrideOther
};

enum Outcome {
	OutcomeUnknown,
	OutcomePass,
	OutcomeFail
};

enum DKIMAuthResult {
	DkimUnknown,
	DkimNone,
	DkimPass,
	DkimFail,
	DkimPolicy,
	DkimNeutral,
	DkimTempError,
	DkimPermError
};

enum SPFAuthResult {
	SpfUnknown,
	SpfNone,
	SpfNeutral,
	SpfPass,
	SpfFail,
	SpfSoftFail,
	SpfTempError,
	SpfPermError
};

class PublishedPolicy;
class DKIMAuthenticationResult;
class SPFAuthenticationResult;
class AuthenticationResults;
class OverrideReason;
class EvaluatedPolicy;
class RecordIdentifier;
class RecordRow;
class Record;
class ReportMetadata;
class Feedback;

DMARCPARSERSHARED_EXPORT DMARC::Feedback* parseReport(const QByteArray& report, QString* error);
DMARCPARSERSHARED_EXPORT DMARC::Feedback* parseReport(const QString& report, QString* error);
DMARCPARSERSHARED_EXPORT DMARC::Feedback* parseReport(QIODevice* report, QString* error);

} // namespace DMARC

#endif // DMARCPARSER_H

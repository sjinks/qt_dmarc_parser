#include <QtCore/QString>
#include "private.h"

DMARC::OverrideType string2ot(const QString& s)
{
	if (QLatin1String("forwarded") == s) {
		return DMARC::OverrideForwarded;
	}

	if (QLatin1String("sampled_out") == s) {
		return DMARC::OverrideSampledOut;
	}

	if (QLatin1String("trusted_forwarder") == s) {
		return DMARC::OverrideSampledOut;
	}

	if (QLatin1String("mailing_list") == s) {
		return DMARC::OverrideMailingList;
	}

	if (QLatin1String("local_policy") == s) {
		return DMARC::OverrideLocalPolicy;
	}

	if (QLatin1String("local_policy") == s) {
		return DMARC::OverrideOther;
	}

	return DMARC::OverrideUnknown;
}

DMARC::Policy string2policy(const QString& s)
{
	if (QLatin1String("s") == s) {
		return DMARC::StrictPolicy;
	}

	if (QLatin1String("r") == s) {
		return DMARC::RelaxedPolicy;
	}

	return DMARC::UnknownPolicy;
}

DMARC::Disposition string2disposition(const QString& s)
{
	if (QLatin1String("none") == s) {
		return DMARC::DispositionNone;
	}

	if (QLatin1String("quarantine") == s) {
		return DMARC::DispositionQuarantine;
	}

	if (QLatin1String("reject") == s) {
		return DMARC::DispositionReject;
	}

	return DMARC::DispositionUnknown;
}

DMARC::Outcome string2outcome(const QString& s)
{
	if (QLatin1String("pass") == s) {
		return DMARC::OutcomePass;
	}

	if (QLatin1String("fail") == s) {
		return DMARC::OutcomeFail;
	}

	return DMARC::OutcomeUnknown;
}

DMARC::DKIMAuthResult string2dkimauthres(const QString& s)
{
	if (QLatin1String("none") == s) {
		return DMARC::DkimNone;
	}

	if (QLatin1String("pass") == s) {
		return DMARC::DkimPass;
	}

	if (QLatin1String("fail") == s) {
		return DMARC::DkimFail;
	}

	if (QLatin1String("policy") == s) {
		return DMARC::DkimPolicy;
	}

	if (QLatin1String("neutral") == s) {
		return DMARC::DkimNeutral;
	}

	if (QLatin1String("temperror") == s) {
		return DMARC::DkimTempError;
	}

	if (QLatin1String("permerror") == s) {
		return DMARC::DkimPermError;
	}

	return DMARC::DkimUnknown;
}

DMARC::SPFAuthResult string2spfauthres(const QString& s)
{
	if (QLatin1String("none") == s) {
		return DMARC::SpfNone;
	}

	if (QLatin1String("neutral") == s) {
		return DMARC::SpfNeutral;
	}

	if (QLatin1String("pass") == s) {
		return DMARC::SpfPass;
	}

	if (QLatin1String("fail") == s) {
		return DMARC::SpfFail;
	}

	if (QLatin1String("softfail") == s) {
		return DMARC::SpfSoftFail;
	}

	if (QLatin1String("temperror") == s) {
		return DMARC::SpfTempError;
	}

	if (QLatin1String("permerror") == s) {
		return DMARC::SpfPermError;
	}

	return DMARC::SpfUnknown;
}

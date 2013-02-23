#ifndef DMARC_PRIVATE_H
#define DMARC_PRIVATE_H

#include "dmarcparser.h"

QT_FORWARD_DECLARE_CLASS(QString)

Q_DECL_HIDDEN DMARC::OverrideType string2ot(const QString& s);
Q_DECL_HIDDEN DMARC::Policy string2policy(const QString& s);
Q_DECL_HIDDEN DMARC::Disposition string2disposition(const QString& s);
Q_DECL_HIDDEN DMARC::Outcome string2outcome(const QString& s);
Q_DECL_HIDDEN DMARC::DKIMAuthResult string2dkimauthres(const QString& s);
Q_DECL_HIDDEN DMARC::SPFAuthResult string2spfauthres(const QString& s);

#endif // DMARC_PRIVATE_H

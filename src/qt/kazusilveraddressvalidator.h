// Copyright (c) 2011-2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KSLVCOIN_QT_KSLVCOINADDRESSVALIDATOR_H
#define KSLVCOIN_QT_KSLVCOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class KazuSilverAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit KazuSilverAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** KazuSilver address widget validator, checks for a valid kazusilver address.
 */
class KazuSilverAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit KazuSilverAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // KSLVCOIN_QT_KSLVCOINADDRESSVALIDATOR_H

/*
 * Copyright (c) 2024, Jamie Mansfield <jmansfield@cadixdev.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/OwnPtr.h>
#include <LibWeb/Preferences/Preferences.h>
#include <QSettings>

namespace Ladybird {

class Preferences
    : public QObject
    , public Web::Preferences::Preferences {
    Q_OBJECT

public:
    Preferences();

    virtual Optional<String> get(String const&) override;
    virtual void set(String const&, String const&) override;

private:
    OwnPtr<QSettings> m_qsettings;
};

}

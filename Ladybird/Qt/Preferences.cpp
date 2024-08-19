/*
 * Copyright (c) 2024, Jamie Mansfield <jmansfield@cadixdev.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "Preferences.h"
#include "Settings.h"
#include "StringUtils.h"

namespace Ladybird {

Preferences::Preferences()
{
    m_qsettings = make<QSettings>(QSettings::IniFormat, QSettings::UserScope, "Ladybird", "Ladybird", this);
}

Optional<String> Preferences::get(String const& key)
{
    // FIXME: This currently converts to the old keys, but it should operate on
    //        QSettings directly.
    if (key == "home.new_tab_url"sv)
        return ak_string_from_qstring(Settings::the()->new_tab_page());
    if (key == "privacy.do_not_track"sv)
        return Settings::the()->enable_do_not_track() ? "true"_string : "false"_string;

    auto qkey = qstring_from_ak_string(key);
    if (!m_qsettings->contains(qkey))
        return {};
    return ak_string_from_qstring(m_qsettings->value(qkey).toString());
}

void Preferences::set(String const& key, String const& value)
{
    // FIXME: This currently converts to the old keys, but it should operate on
    //        QSettings directly.
    if (key == "home.new_tab_url"sv)
        Settings::the()->set_new_tab_page(qstring_from_ak_string(value));
    if (key == "privacy.do_not_track"sv)
        Settings::the()->set_enable_do_not_track(value.equals_ignoring_ascii_case("true"sv));

    m_qsettings->setValue(qstring_from_ak_string(key), qstring_from_ak_string(value));
}

}

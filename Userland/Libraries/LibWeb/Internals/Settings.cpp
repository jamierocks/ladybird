/*
 * Copyright (c) 2024, Jamie Mansfield <jmansfield@cadixdev.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibWeb/Bindings/Intrinsics.h>
#include <LibWeb/Bindings/SettingsPrototype.h>
#include <LibWeb/HTML/Window.h>
#include <LibWeb/Internals/Settings.h>
#include <LibWeb/Preferences/Preferences.h>

namespace Web::Internals {

JS_DEFINE_ALLOCATOR(Settings);

Settings::Settings(JS::Realm& realm)
   : PlatformObject(realm)
{
}

void Settings::initialize(JS::Realm& realm)
{
   Base::initialize(realm);
   WEB_SET_PROTOTYPE_FOR_INTERFACE(Settings);
}

String Settings::get(String const& key) const
{
    return Preferences::Preferences::the().get(key).value_or({});
}

void Settings::set(String const& key, String const& value)
{
    Preferences::Preferences::the().set(key, value);
}

}

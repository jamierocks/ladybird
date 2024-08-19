/*
 * Copyright (c) 2024, Jamie Mansfield <jmansfield@cadixdev.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <AK/Assertions.h>
#include <LibWeb/Preferences/Preferences.h>

namespace Web::Preferences {

Preferences* Preferences::s_the = nullptr;

Preferences::Preferences()
{
    VERIFY(!s_the);
    s_the = this;
}

Preferences::~Preferences()
{
    s_the = nullptr;
}

}

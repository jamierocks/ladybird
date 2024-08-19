/*
 * Copyright (c) 2024, Jamie Mansfield <jmansfield@cadixdev.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/Noncopyable.h>
#include <AK/String.h>

namespace Web::Preferences {

class Preferences {
    AK_MAKE_NONCOPYABLE(Preferences);

public:
    virtual ~Preferences();

    static Preferences& the() { return *s_the; }

    virtual Optional<String> get(String const&) { return {}; };
    virtual void set(String const&, String const&) { };

protected:
    Preferences();

private:
    static Preferences* s_the;
};

}

/*
 * Copyright (c) 2024, Jamie Mansfield <jmansfield@cadixdev.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibWeb/Bindings/PlatformObject.h>

namespace Web::Internals {

class Settings final : public Bindings::PlatformObject {
   WEB_PLATFORM_OBJECT(Settings, Bindings::PlatformObject);
   JS_DECLARE_ALLOCATOR(Settings);

public:
   virtual ~Settings() override = default;

   String get(String const& key) const;
   void set(String const& key, String const& value);

private:
   explicit Settings(JS::Realm&);

   virtual void initialize(JS::Realm&) override;
};

}

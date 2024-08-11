/*
 * Copyright (c) 2024, Jamie Mansfield <jmansfield@cadixdev.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibJS/Runtime/Realm.h>
#include <LibWeb/Bindings/StorageEventPrototype.h>
#include <LibWeb/Bindings/Intrinsics.h>
#include <LibWeb/HTML/Storage.h>
#include <LibWeb/HTML/StorageEvent.h>

namespace Web::HTML {

JS_DEFINE_ALLOCATOR(StorageEvent);

[[nodiscard]] JS::NonnullGCPtr<StorageEvent> StorageEvent::create(JS::Realm& realm, FlyString const& event_name, StorageEventInit const& event_init)
{
   return realm.heap().allocate<StorageEvent>(realm, realm, event_name, event_init);
}

JS::NonnullGCPtr<StorageEvent> StorageEvent::construct_impl(JS::Realm& realm, FlyString const& event_name, StorageEventInit const& event_init)
{
   return realm.heap().allocate<StorageEvent>(realm, realm, event_name, event_init);
}

StorageEvent::StorageEvent(JS::Realm& realm, FlyString const& event_name, StorageEventInit const& event_init)
   : DOM::Event(realm, event_name, event_init)
   , m_key(event_init.key)
   , m_old_value(event_init.old_value)
   , m_new_value(event_init.new_value)
   , m_url(event_init.url)
   , m_storage_area(event_init.storage_area)
{
}

void StorageEvent::initialize(JS::Realm& realm)
{
   Base::initialize(realm);
   WEB_SET_PROTOTYPE_FOR_INTERFACE(StorageEvent);
}

void StorageEvent::visit_edges(Visitor& visitor)
{
   Base::visit_edges(visitor);
   visitor.visit(m_storage_area);
}

}

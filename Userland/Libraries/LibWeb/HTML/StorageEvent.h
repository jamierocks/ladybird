/*
 * Copyright (c) 2024, Jamie Mansfield <jmansfield@cadixdev.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibWeb/DOM/Event.h>

namespace Web::HTML {

// https://html.spec.whatwg.org/multipage/webstorage.html#storageeventinit
struct StorageEventInit : public DOM::EventInit {
   Optional<String> key = {};
   Optional<String> old_value = {};
   Optional<String> new_value = {};
   String url;
   JS::GCPtr<Storage> storage_area;
};

// https://html.spec.whatwg.org/multipage/webstorage.html#storageevent
class StorageEvent final : public DOM::Event {
   WEB_PLATFORM_OBJECT(StorageEvent, DOM::Event);
   JS_DECLARE_ALLOCATOR(StorageEvent);

public:
   [[nodiscard]] static JS::NonnullGCPtr<StorageEvent> create(JS::Realm&, FlyString const& event_name, StorageEventInit const&);
   [[nodiscard]] static JS::NonnullGCPtr<StorageEvent> construct_impl(JS::Realm&, FlyString const& event_name, StorageEventInit const&);

   Optional<String> key() { return m_key; }
   Optional<String> old_value() { return m_old_value; }
   Optional<String> new_value() { return m_new_value; }
   String url() { return m_url; }
   JS::GCPtr<Storage> storage_area() { return m_storage_area; }

private:
   StorageEvent(JS::Realm&, FlyString const& event_name, StorageEventInit const& event_init);

   virtual void initialize(JS::Realm&) override;
   virtual void visit_edges(Visitor& visitor) override;

   Optional<String> m_key;
   Optional<String> m_old_value;
   Optional<String> m_new_value;
   String m_url;
   JS::GCPtr<Storage> m_storage_area;
};

}

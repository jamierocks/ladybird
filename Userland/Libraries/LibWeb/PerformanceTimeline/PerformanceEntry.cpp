/*
 * Copyright (c) 2023, Luke Wilde <lukew@serenityos.org>
 * Copyright (c) 2024, Jamie Mansfield <jmansfield@cadixdev.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibWeb/Bindings/Intrinsics.h>
#include <LibWeb/Bindings/PerformanceEntryPrototype.h>
#include <LibWeb/PerformanceTimeline/PerformanceEntry.h>

namespace Web::PerformanceTimeline {

PerformanceEntry::PerformanceEntry(JS::Realm& realm)
    : Bindings::PlatformObject(realm)
{
}

// NOTE: This constructor is provided for performance entries that haven't updated following changes to the spec.
//       See https://github.com/w3c/performance-timeline/pull/210
PerformanceEntry::PerformanceEntry(JS::Realm& realm, HighResolutionTime::DOMHighResTimeStamp start_time, FlyString const& entry_type, String const& name, HighResolutionTime::DOMHighResTimeStamp end_time)
    : Bindings::PlatformObject(realm)
{
    initialise_entry(start_time, entry_type, name, end_time);
}

PerformanceEntry::~PerformanceEntry() = default;

void PerformanceEntry::initialize(JS::Realm& realm)
{
    Base::initialize(realm);
    WEB_SET_PROTOTYPE_FOR_INTERFACE(PerformanceEntry);
}

// https://www.w3.org/TR/performance-timeline/#dom-performanceentry-duration
HighResolutionTime::DOMHighResTimeStamp PerformanceEntry::duration() const
{
    // The getter steps for the duration attribute are to return 0 if this's end time is 0;
    // otherwise this's end time - this's startTime.
    if (m_end_time == 0)
        return 0;

    return m_end_time - m_start_time;
}

// https://www.w3.org/TR/performance-timeline/#dfn-initialize-a-performanceentry
void PerformanceEntry::initialise_entry(HighResolutionTime::DOMHighResTimeStamp start_time, FlyString const& entry_type, String const& name, HighResolutionTime::DOMHighResTimeStamp end_time)
{
    // FIXME: 1. Assert: entryType is defined in the entry type registry.

    // 2. Initialize entry's startTime to startTime.
    m_start_time = start_time;

    // 3. Initialize entry's entryType to entryType.
    m_entry_type = entry_type;

    // 4. Initialize entry's name to name.
    m_name = name;

    // 5. Initialize entry's end time to endTime.
    m_end_time = end_time;
}

}

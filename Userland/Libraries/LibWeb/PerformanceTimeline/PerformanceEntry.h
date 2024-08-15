/*
 * Copyright (c) 2023, Luke Wilde <lukew@serenityos.org>
 * Copyright (c) 2024, Jamie Mansfield <jmansfield@cadixdev.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibWeb/Bindings/PlatformObject.h>
#include <LibWeb/HighResolutionTime/DOMHighResTimeStamp.h>

namespace Web::PerformanceTimeline {

enum class AvailableFromTimeline {
    No,
    Yes,
};

enum class ShouldAddEntry {
    No,
    Yes,
};

// https://www.w3.org/TR/performance-timeline/#dom-performanceentry
class PerformanceEntry : public Bindings::PlatformObject {
    WEB_PLATFORM_OBJECT(PerformanceEntry, Bindings::PlatformObject);

public:
    virtual ~PerformanceEntry();

    String const& name() const { return m_name; }
    FlyString const& entry_type() const { return m_entry_type; }
    HighResolutionTime::DOMHighResTimeStamp start_time() const { return m_start_time; }
    HighResolutionTime::DOMHighResTimeStamp duration() const;

    // https://w3c.github.io/timing-entrytypes-registry/#dfn-should-add-entry
    virtual PerformanceTimeline::ShouldAddEntry should_add_entry(Optional<PerformanceObserverInit const&> = {}) const = 0;

protected:
    PerformanceEntry(JS::Realm&);
    PerformanceEntry(JS::Realm&, HighResolutionTime::DOMHighResTimeStamp start_time, FlyString const& entry_type, String const& name, HighResolutionTime::DOMHighResTimeStamp end_time);
    virtual void initialize(JS::Realm&) override;

    // https://www.w3.org/TR/performance-timeline/#dfn-initialize-a-performanceentry
    void initialise_entry(HighResolutionTime::DOMHighResTimeStamp start_time, FlyString const& entry_type, String const& name, HighResolutionTime::DOMHighResTimeStamp end_time = 0);

private:
    // https://www.w3.org/TR/performance-timeline/#dom-performanceentry-name
    String m_name;

    // https://www.w3.org/TR/performance-timeline/#dom-performanceentry-entrytype
    FlyString m_entry_type;

    // https://www.w3.org/TR/performance-timeline/#dom-performanceentry-starttime
    HighResolutionTime::DOMHighResTimeStamp m_start_time { 0.0 };

    // https://www.w3.org/TR/performance-timeline/#dfn-end-time
    HighResolutionTime::DOMHighResTimeStamp m_end_time { 0.0 };
};

}

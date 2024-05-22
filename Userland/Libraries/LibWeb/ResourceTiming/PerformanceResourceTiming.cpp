/*
 * Copyright (c) 2024, Jamie Mansfield <jmansfield@cadixdev.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibWeb/Bindings/Intrinsics.h>
#include <LibWeb/Bindings/PerformanceResourceTimingPrototype.h>
#include <LibWeb/Fetch/Infrastructure/FetchTimingInfo.h>
#include <LibWeb/ResourceTiming/PerformanceResourceTiming.h>

namespace Web::ResourceTiming {

JS_DEFINE_ALLOCATOR(PerformanceResourceTiming);

PerformanceResourceTiming::PerformanceResourceTiming(JS::Realm& realm)
    : PerformanceTimeline::PerformanceEntry(realm)
{
}

PerformanceResourceTiming::~PerformanceResourceTiming() = default;

JS::NonnullGCPtr<PerformanceResourceTiming> PerformanceResourceTiming::create(JS::Realm& realm)
{
    return realm.heap().allocate<PerformanceResourceTiming>(realm, realm);
}

void PerformanceResourceTiming::initialize(JS::Realm& realm)
{
    Base::initialize(realm);
    WEB_SET_PROTOTYPE_FOR_INTERFACE(PerformanceResourceTiming);
}

void PerformanceResourceTiming::visit_edges(Visitor& visitor)
{
    Base::visit_edges(visitor);
    visitor.visit(m_timing_info);
}

// https://w3c.github.io/resource-timing/#dfn-setup-the-resource-timing-entry
void PerformanceResourceTiming::setup(String const& initiator_type, String const& requested_url, Fetch::Infrastructure::FetchTimingInfo& timing_info, String const& cache_mode, Fetch::Infrastructure::Response::BodyInfo body_info, u16 response_status, String delivery_type)
{
    // 1. Assert that cacheMode is the empty string, "local", or "validated".
    VERIFY(cache_mode.is_empty() || cache_mode == "local" || cache_mode == "validated");

    // 2. Let global be entry's relevant global object.
    // 3. Initialize entry given the result of converting timingInfo's start time given global, "resource", requestedURL, and the result of converting timingInfo's end time given global.
    initialise_entry(timing_info.start_time(), PerformanceTimeline::EntryTypes::resource, requested_url, timing_info.end_time());

    // 4. Set entry's initiator type to initiatorType.
    m_initiator_type = initiator_type;

    // 5. Set entry's requested URL to requestedURL.
    m_requested_url = requested_url;

    // 6. Set entry's timing info to timingInfo.
    m_timing_info = timing_info;

    // 7. Set entry's response body info to bodyInfo.
    m_resource_info = body_info;

    // 8. Set entry's cache mode to cacheMode.
    m_cache_mode = cache_mode;

    // 9. Set entry's response status to responseStatus.
    m_response_status = response_status;

    // 10. If deliveryType is the empty string and cacheMode is not, then set deliveryType to "cache".
    if (delivery_type.is_empty() && !cache_mode.is_empty())
        delivery_type = "cache"_string;

    // 11. Set entry's delivery type to deliveryType.
    m_delivery_type = delivery_type;
}

// https://w3c.github.io/resource-timing/#dom-performanceresourcetiming-transfersize
WebIDL::UnsignedLongLong PerformanceResourceTiming::transfer_size()
{
    // 1. If this's cache mode is "local", then return 0.
    if (m_cache_mode.equals_ignoring_ascii_case("local"sv))
        return 0;

    // 2. If this's cache mode is "validated", then return 300.
    if (m_cache_mode.equals_ignoring_ascii_case("validated"sv))
        return 300;

    // 3. Return this's response body info's encoded size plus 300.
    return m_resource_info.encoded_size + 300;
}

}

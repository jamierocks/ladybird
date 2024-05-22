/*
 * Copyright (c) 2024, Jamie Mansfield <jmansfield@cadixdev.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibWeb/HTML/WindowOrWorkerGlobalScope.h>
#include <LibWeb/ResourceTiming/AbstractOperations.h>
#include <LibWeb/ResourceTiming/PerformanceResourceTiming.h>

namespace Web::ResourceTiming {

// https://w3c.github.io/resource-timing/#dfn-mark-resource-timing
void mark_resource_timing(Fetch::Infrastructure::FetchTimingInfo& timing_info, String const& requested_url, String const& initiator_type, JS::Object& global, String const& cache_mode, Fetch::Infrastructure::Response::BodyInfo body_info, u16 response_status, String const& delivery_type)
{
    auto* window_or_worker = dynamic_cast<HTML::WindowOrWorkerGlobalScopeMixin*>(&global);
    VERIFY(window_or_worker);

    // 1. Create a PerformanceResourceTiming object entry in global's realm.
    auto entry = PerformanceResourceTiming::create(*global.vm().current_realm());

    // 2. Setup the resource timing entry for entry, given initiatorType, requestedURL, timingInfo, cacheMode, bodyInfo, responseStatus, and deliveryType.
    entry->setup(initiator_type, requested_url, timing_info, cache_mode, body_info, response_status, delivery_type);

    // 3. Queue entry.
    window_or_worker->queue_performance_entry(entry);

    // 4. Add entry to global's performance entry buffer.
    window_or_worker->add_resource_timing_entry(entry);
}

}

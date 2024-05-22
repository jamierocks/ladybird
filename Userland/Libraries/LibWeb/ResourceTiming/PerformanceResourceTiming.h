/*
 * Copyright (c) 2024, Jamie Mansfield <jmansfield@cadixdev.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibWeb/Fetch/Response.h>
#include <LibWeb/Fetch/Infrastructure/ConnectionTimingInfo.h>
#include <LibWeb/Fetch/Infrastructure/FetchTimingInfo.h>
#include <LibWeb/PerformanceTimeline/EntryTypes.h>
#include <LibWeb/PerformanceTimeline/PerformanceEntry.h>
#include <LibWeb/WebIDL/Types.h>

namespace Web::ResourceTiming {

// https://w3c.github.io/resource-timing/#dom-performanceresourcetiming
class PerformanceResourceTiming final : public PerformanceTimeline::PerformanceEntry {
    WEB_PLATFORM_OBJECT(PerformanceResourceTiming, PerformanceTimeline::PerformanceEntry);
    JS_DECLARE_ALLOCATOR(PerformanceResourceTiming);

public:
    ~PerformanceResourceTiming();

    [[nodiscard]] static JS::NonnullGCPtr<PerformanceResourceTiming> create(JS::Realm&);

    void setup(String const& initiator_type, String const& requested_url, Fetch::Infrastructure::FetchTimingInfo& timing_info, String const& cache_mode, Fetch::Infrastructure::Response::BodyInfo body_info, u16 response_status, String delivery_type);

    PerformanceTimeline::ShouldAddEntry should_add_entry(Optional<PerformanceTimeline::PerformanceObserverInit const&> = {}) const override { return PerformanceTimeline::ShouldAddEntry::Yes; };

    String const& initiator_type() { return m_initiator_type; }
    String const& delivery_type() { return m_delivery_type; }
    HighResolutionTime::DOMHighResTimeStamp worker_start() { return m_timing_info->final_service_worker_start_time(); }
    HighResolutionTime::DOMHighResTimeStamp redirect_start() { return m_timing_info->redirect_start_time(); }
    HighResolutionTime::DOMHighResTimeStamp redirect_end() { return m_timing_info->redirect_end_time(); }
    HighResolutionTime::DOMHighResTimeStamp fetch_start() { return m_timing_info->post_redirect_start_time(); }
    HighResolutionTime::DOMHighResTimeStamp domain_lookup_start() { return m_timing_info->final_connection_timing_info()->domain_lookup_start_time(); }
    HighResolutionTime::DOMHighResTimeStamp domain_lookup_end() { return m_timing_info->final_connection_timing_info()->domain_lookup_end_time(); }
    HighResolutionTime::DOMHighResTimeStamp connect_start() { return m_timing_info->final_connection_timing_info()->connection_start_time(); }
    HighResolutionTime::DOMHighResTimeStamp connect_end() { return m_timing_info->final_connection_timing_info()->connection_end_time(); }
    HighResolutionTime::DOMHighResTimeStamp secure_connection_start() { return m_timing_info->final_connection_timing_info()->secure_connection_start_time(); }
    HighResolutionTime::DOMHighResTimeStamp request_start() { return m_timing_info->final_network_request_start_time(); }
    HighResolutionTime::DOMHighResTimeStamp response_start() { return m_timing_info->final_network_response_start_time(); }
    HighResolutionTime::DOMHighResTimeStamp response_end() { return m_timing_info->end_time(); }
    WebIDL::UnsignedLongLong transfer_size();
    WebIDL::UnsignedLongLong encoded_body_size() { return m_resource_info.encoded_size; }
    WebIDL::UnsignedLongLong decoded_body_size() { return m_resource_info.decoded_size; }
    u16 response_status() { return m_response_status; }
    String const& content_type() { return m_resource_info.content_type; }

private:
    PerformanceResourceTiming(JS::Realm&);

    virtual void initialize(JS::Realm&) override;
    virtual void visit_edges(Visitor&) override;

    // https://w3c.github.io/resource-timing/#dfn-initiator-type
    String m_initiator_type;

    // https://w3c.github.io/resource-timing/#dfn-delivery-type
    String m_delivery_type;

    // https://w3c.github.io/resource-timing/#dfn-requested-url
    String m_requested_url;

    // https://w3c.github.io/resource-timing/#dfn-cache-mode
    String m_cache_mode;

    // https://w3c.github.io/resource-timing/#dfn-timing-info
    JS::GCPtr<Fetch::Infrastructure::FetchTimingInfo> m_timing_info;

    // https://w3c.github.io/resource-timing/#dfn-resource-info
    Fetch::Infrastructure::Response::BodyInfo m_resource_info;

    // https://w3c.github.io/resource-timing/#dfn-response-status
    u16 m_response_status;

    // https://w3c.github.io/resource-timing/#dfn-render-blocking-status
    // FIXME: render blocking status
};

}

/*
 * Copyright (c) 2024, Jamie Mansfield <jmansfield@cadixdev.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibWeb/Fetch/Response.h>

namespace Web::ResourceTiming {

// https://w3c.github.io/resource-timing/#dfn-mark-resource-timing
void mark_resource_timing(Fetch::Infrastructure::FetchTimingInfo& timing_info, String const& requested_url, String const& initiator_type, JS::Object& global, String const& cache_mode, Fetch::Infrastructure::Response::BodyInfo body_info, u16 response_status, String const& delivery_type = ""_string);

}

/*
 * Copyright (c) 2024, Jamie Mansfield <jmansfield@cadixdev.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/String.h>

namespace Web::MediaSession {

struct MediaImage {
    String src;
    String sizes = ""_string;
    String type = ""_string;
};

}

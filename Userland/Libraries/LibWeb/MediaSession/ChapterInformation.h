/*
 * Copyright (c) 2024, Jamie Mansfield <jmansfield@cadixdev.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibWeb/Bindings/PlatformObject.h>
#include <LibWeb/MediaSession/MediaImage.h>
#include <LibWeb/WebIDL/Types.h>

namespace Web::MediaSession {

struct ChapterInformationInit {
    String title = ""_string;
    double start_time = 0;
    Vector<MediaImage> artwork;
};

class ChapterInformation final : public Bindings::PlatformObject {
    WEB_PLATFORM_OBJECT(ChapterInformation, Bindings::PlatformObject);
    JS_DECLARE_ALLOCATOR(ChapterInformation);

public:
    static WebIDL::ExceptionOr<JS::NonnullGCPtr<ChapterInformation>> create(JS::Realm&, ChapterInformationInit const&);
    virtual ~ChapterInformation() override = default;

    String title() const { return m_title; }
    double start_time() const { return m_start_time; }

private:
    explicit ChapterInformation(JS::Realm&, ChapterInformationInit const&);

    virtual void initialize(JS::Realm&) override;

    String m_title;
    double m_start_time;
    Vector<MediaImage> m_artwork;
};

}

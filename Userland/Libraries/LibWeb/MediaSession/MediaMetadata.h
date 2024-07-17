/*
 * Copyright (c) 2024, Jamie Mansfield <jmansfield@cadixdev.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibWeb/Bindings/PlatformObject.h>
#include <LibWeb/MediaSession/ChapterInformation.h>
#include <LibWeb/WebIDL/Types.h>

namespace Web::MediaSession {

struct MediaMetadataInit {
   String title = ""_string;
   String artist = ""_string;
   String album = ""_string;
   Vector<MediaImage> artwork;
   Vector<ChapterInformationInit> chapter_info;
};

class MediaMetadata final : public Bindings::PlatformObject {
   WEB_PLATFORM_OBJECT(MediaMetadata, Bindings::PlatformObject);
   JS_DECLARE_ALLOCATOR(MediaMetadata);

public:
   static WebIDL::ExceptionOr<JS::NonnullGCPtr<MediaMetadata>> construct_impl(JS::Realm&, MediaMetadataInit const&);
   virtual ~MediaMetadata() override = default;

   String title() const { return m_title; }
   String artist() const { return m_artist; }
   String album() const { return m_album; }

private:
   explicit MediaMetadata(JS::Realm&, MediaMetadataInit const&);

   virtual void initialize(JS::Realm&) override;
   virtual void visit_edges(Cell::Visitor&) override;

   String m_title;
   String m_artist;
   String m_album;
   Vector<MediaImage> m_artwork;
   Vector<ChapterInformation> m_chapter_information;
};

}

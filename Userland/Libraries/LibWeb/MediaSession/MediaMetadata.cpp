/*
 * Copyright (c) 2024, Jamie Mansfield <jmansfield@cadixdev.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibWeb/Bindings/Intrinsics.h>
#include <LibWeb/Bindings/MediaMetadataPrototype.h>
#include <LibWeb/MediaSession/MediaMetadata.h>
#include <LibWeb/WebIDL/ExceptionOr.h>

namespace Web::MediaSession {

JS_DEFINE_ALLOCATOR(MediaMetadata);

WebIDL::ExceptionOr<JS::NonnullGCPtr<MediaMetadata>> MediaMetadata::construct_impl(JS::Realm& realm, MediaMetadataInit const& media_metadata_init)
{
   return realm.heap().allocate<MediaMetadata>(realm, realm, media_metadata_init);
}

MediaMetadata::MediaMetadata(JS::Realm& realm, MediaMetadataInit const& media_metadata_init)
   : PlatformObject(realm)
   , m_title(media_metadata_init.title)
   , m_artist(media_metadata_init.artist)
   , m_album(media_metadata_init.album)
   , m_artwork(media_metadata_init.artwork)
{
    // FIXME: chapters
}

void MediaMetadata::initialize(JS::Realm& realm)
{
   Base::initialize(realm);
   WEB_SET_PROTOTYPE_FOR_INTERFACE(MediaMetadata);
}

void MediaMetadata::visit_edges(Cell::Visitor& visitor)
{
    Base::visit_edges(visitor);
//    visitor.visit(m_chapter_information);
}

}

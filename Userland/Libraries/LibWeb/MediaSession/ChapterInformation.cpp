/*
 * Copyright (c) 2024, Jamie Mansfield <jmansfield@cadixdev.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibWeb/Bindings/Intrinsics.h>
#include <LibWeb/Bindings/ChapterInformationPrototype.h>
#include <LibWeb/MediaSession/ChapterInformation.h>
#include <LibWeb/WebIDL/ExceptionOr.h>

namespace Web::MediaSession {

JS_DEFINE_ALLOCATOR(ChapterInformation);

WebIDL::ExceptionOr<JS::NonnullGCPtr<ChapterInformation>> ChapterInformation::create(JS::Realm& realm, ChapterInformationInit const& chapter_information_init)
{
    return realm.heap().allocate<ChapterInformation>(realm, realm, chapter_information_init);
}

ChapterInformation::ChapterInformation(JS::Realm& realm, ChapterInformationInit const& chapter_information_init)
    : PlatformObject(realm)
    , m_title(chapter_information_init.title)
    , m_start_time(chapter_information_init.start_time)
    , m_artwork(chapter_information_init.artwork)
{
}

void ChapterInformation::initialize(JS::Realm& realm)
{
    Base::initialize(realm);
    WEB_SET_PROTOTYPE_FOR_INTERFACE(ChapterInformation);
}

}

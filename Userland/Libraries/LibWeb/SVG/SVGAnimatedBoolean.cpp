/*
 * Copyright (c) 2024, Jamie Mansfield <jmansfield@cadixdev.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibWeb/Bindings/Intrinsics.h>
#include <LibWeb/Bindings/SVGAnimatedBooleanPrototype.h>
#include <LibWeb/SVG/SVGAnimatedBoolean.h>
#include <LibWeb/SVG/SVGElement.h>

namespace Web::SVG {

JS_DEFINE_ALLOCATOR(SVGAnimatedBoolean);

JS::NonnullGCPtr<SVGAnimatedBoolean> SVGAnimatedBoolean::create(JS::Realm& realm, JS::NonnullGCPtr<SVGElement> element, FlyString reflected_attribute, bool initial_value)
{
    return realm.heap().allocate<SVGAnimatedBoolean>(realm, realm, element, reflected_attribute, initial_value);
}

SVGAnimatedBoolean::SVGAnimatedBoolean(JS::Realm& realm, JS::NonnullGCPtr<SVGElement> element, FlyString reflected_attribute, bool initial_value)
    : PlatformObject(realm)
    , m_element(element)
    , m_reflected_attribute(move(reflected_attribute))
    , m_initial_value(initial_value)
{
}

SVGAnimatedBoolean::~SVGAnimatedBoolean() = default;

void SVGAnimatedBoolean::initialize(JS::Realm& realm)
{
    Base::initialize(realm);
    WEB_SET_PROTOTYPE_FOR_INTERFACE(SVGAnimatedBoolean);
}

void SVGAnimatedBoolean::visit_edges(Visitor& visitor)
{
    Base::visit_edges(visitor);
    visitor.visit(m_element);
}

// https://svgwg.org/svg2-draft/types.html#__svg__SVGAnimatedBoolean__baseVal
bool SVGAnimatedBoolean::base_val() const
{
    // On getting baseVal or animVal, the following steps are run:

    // 1. Let value be the value of the reflected attribute, or the empty string if it is not present.
    auto value = m_element->attribute(m_reflected_attribute).value_or(""_string);

    // 2. If value is not "true" or "false", then set value to the reflected attribute's initial value.
    if (value != "true"_string && value != "false"_string)
        value = m_initial_value ? "true"_string : "false"_string;

    // 3. Return true if value is "true", and false otherwise.
    return value == "true"_string;
}

// https://svgwg.org/svg2-draft/types.html#__svg__SVGAnimatedBoolean__baseVal
void SVGAnimatedBoolean::set_base_val(bool value)
{
    // On setting baseVal, the reflected attribute is set to "true" if the value is true, and "false" otherwise.
    MUST(m_element->set_attribute(m_reflected_attribute, value ? "true"_string : "false"_string));
}

}

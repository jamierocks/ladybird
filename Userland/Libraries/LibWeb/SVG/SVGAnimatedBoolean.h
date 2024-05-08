/*
 * Copyright (c) 2024, Jamie Mansfield <jmansfield@cadixdev.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibWeb/Bindings/PlatformObject.h>

namespace Web::SVG {

// https://svgwg.org/svg2-draft/types.html#InterfaceSVGAnimatedBoolean
class SVGAnimatedBoolean final : public Bindings::PlatformObject {
    WEB_PLATFORM_OBJECT(SVGAnimatedBoolean, Bindings::PlatformObject);
    JS_DECLARE_ALLOCATOR(SVGAnimatedBoolean);

public:
    [[nodiscard]] static JS::NonnullGCPtr<SVGAnimatedBoolean> create(JS::Realm&, JS::NonnullGCPtr<SVGElement> element, FlyString reflected_attribute, bool initial_value);
    virtual ~SVGAnimatedBoolean() override;

    bool base_val() const;
    void set_base_val(bool value);

private:
    SVGAnimatedBoolean(JS::Realm&, JS::NonnullGCPtr<SVGElement> element, FlyString reflected_attribute, bool initial_value);

    virtual void initialize(JS::Realm&) override;
    virtual void visit_edges(Visitor&) override;

    JS::NonnullGCPtr<SVGElement> m_element;
    FlyString m_reflected_attribute;
    bool m_initial_value;
};

}

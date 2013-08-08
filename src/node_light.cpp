#include "node_light.h"

#include <GL/gl.h>
#include <cmath>
#include <glm/gtc/type_ptr.hpp>

namespace Scene {
    Light::Light(string_type const & __s,
            ptr_node_type const & __p):
        Node(__s, __p),
        _intensity(1),
        _radius(1),
        _quality(1),
        _color()
    {
    }

    Light::~Light() {
    }

    Light::intensity_type const & Light::intensity() const {
        return _intensity;
    }

    void Light::intensity(intensity_type const & __i) {
        _intensity = __i;
    }

    Light::dim_type const & Light::radius() const {
        return _radius;
    }

    void Light::radius(dim_type const & __r) {
        _radius = __r;
    }

    Light::quality_type const & Light::quality() const {
        return _quality;
    }

    void Light::quality(quality_type const & __q) {
        _quality = __q;
    }

    Light::color_type const & Light::color() const {
        return _color;
    }

    void Light::color(color_type const & __c) {
        _color = __c;
    }

    void Light::color(float __r, float __g, float __b) {
        _color.r = __r;
        _color.g = __g;
        _color.b = __b;
    }

    void Light::draw_triangle(float x1, float y1, float x2, float y2) const {
        intensity_type intensity;
        glBegin(GL_TRIANGLES);

        // Center point
        intensity = _intensity;
        glColor4f(_color.r * intensity,
                _color.g * intensity,
                _color.b * intensity,
                intensity);
        glVertex3f(0.0f, 0.0f, 0.0f);

        // One extrem point
        intensity = _intensity * (1.0f - std::sqrt(x1 * x1 + y1 * y1) / _radius);
        glColor4f(_color.r * intensity,
                _color.g * intensity,
                _color.b * intensity,
                intensity);
        glVertex3f(x1, y1, 0.0f);

        // Second extrem point
        intensity = _intensity * (1.0f - std::sqrt(x2 * x2 + y2 * y2) / _radius);
        glColor4f(_color.r * intensity,
                _color.g * intensity,
                _color.b * intensity,
                intensity);
        glVertex3f(x2, y2, 0.0f);
        glEnd();
    }

    void Light::draw(transform_type const & __t) const {
        // TODO put gl query to a front level and draw all the scene with
        // more than one pass
        // Additive blending
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);

        glLoadMatrixf(glm::value_ptr(__t));

        float buf = (static_cast<float>(M_PI) * 2.0f)
            / static_cast<float>(_quality);
        for(quality_type i(0) ; i < _quality ; i++) {
            float fi = static_cast<float>(i);
            float x1 = _radius * std::cos(fi * buf);
            float y1 = _radius * std::sin(fi * buf);
            float x2 = _radius * std::cos((fi + 1.0f) * buf);
            float y2 = _radius * std::sin((fi + 1.0f)* buf);

            draw_triangle(x1, y1, x2, y2);
        }
    }
}

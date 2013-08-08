#include "node_graphic.h"

#include <GL/gl.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Scene {
    Graphic::Graphic(string_type const & __s,
            ptr_node_type const & __p):
        Node(__s, __p),
        _texture(nullptr)
    {
    }

    Graphic::~Graphic() {
    }

    Graphic::ptr_texture_type const & Graphic::texture() const {
        return _texture;
    }

    void Graphic::texture(ptr_texture_type const & __t) {
        _texture = __t;
    }

    void Graphic::draw(transform_type const & __t) const {
        if(_texture == nullptr)
            return;

        transform_type t = __t * glm::scale(glm::mat4(),
                glm::vec3(_texture->width(), _texture->height(), 1.0f));

        glLoadMatrixf(glm::value_ptr(t));

        // Alpha blending
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glBindTexture(GL_TEXTURE_2D, _texture->id());
        glBegin(GL_POLYGON);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(1.0f, 1.0f, 0.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(1.0f, 0.0f, 0.0f);
        glEnd();
    }
}

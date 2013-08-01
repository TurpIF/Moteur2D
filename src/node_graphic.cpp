#include "node_graphic.h"

namespace Scene {
    Graphic::Graphic(string_type const & __s,
            ptr_node_type const & __p):
        Node(__s, __p),
        _texture()
    {
    }

    Graphic::~Graphic() {
    }

    Graphic::texture_type const & Graphic::texture() const {
        return _texture;
    }

    void Graphic::texture(texture_type const & __t) {
        _texture = __t;
    }
}

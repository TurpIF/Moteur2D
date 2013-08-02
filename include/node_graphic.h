#ifndef SCENE_GRAPHIC_H
#define SCENE_GRAPHIC_H

#include "node.h"

namespace Scene {
    class Graphic: public Node {
        public:
            Graphic(Graphic &&) = default;
            Graphic(Graphic const &) = delete;
            Graphic & operator=(Graphic const &) = delete;

            Graphic(string_type const & = string_type(),
                    ptr_node_type const & = nullptr);
            virtual ~Graphic();

            ptr_texture_type const & texture() const;
            void texture(ptr_texture_type const &);

        protected:
            virtual void draw(transform_type const &) const;

            ptr_texture_type _texture;
    };
}

#endif

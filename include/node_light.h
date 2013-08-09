#ifndef SCENE_LIGHT_H
#define SCENE_LIGHT_H

#include "node.h"

#include "type.h"

namespace Scene {
    class Light: public Node {
        public:
            typedef float intensity_type;
            typedef numeric<std::size_t> quality_type;

            struct color_type {
                float r;
                float g;
                float b;
            };

            Light() = delete;
            Light(Light const &) = delete;
            Light & operator=(Light const &) = delete;
            Light(Light &&) = default;

            Light(string_type const & = string_type(),
                    ptr_node_type const & = nullptr);
            virtual ~Light();

            intensity_type const & intensity() const;
            void intensity(intensity_type const &);

            dim_type const & radius() const;
            void radius(dim_type const &);

            quality_type const & quality() const;
            void quality(quality_type const &);

            color_type const & color() const;
            void color(color_type const &);
            void color(float, float, float);

        protected:
            virtual void draw(transform_type const &) const;
            void draw_triangle(float, float, float, float) const;

            intensity_type _intensity;
            dim_type _radius;
            quality_type _quality;
            color_type _color;
    };
}

#endif

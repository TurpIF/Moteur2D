#ifndef SCENE_NODE_H
#define SCENE_NODE_H

#include <set>
#include <string>
#include <glm/glm.hpp>

#include "texture.h"

namespace Scene {
    class Node {
        public:
            typedef unsigned int        id_type;
            typedef std::string         string_type;

            typedef float               dim_type;
            typedef glm::mat4           transform_type;
            typedef glm::mediump_float  rotation_type;
            typedef glm::vec3           translation_type;
            typedef glm::vec2           scale_type;
            typedef glm::mediump_float  scalaire_type;
            typedef glm::vec4           rectangle_type;
            typedef Texture *           ptr_texture_type;

            typedef Node * ptr_node_type;
            typedef std::set<ptr_node_type> node_set_type;

            Node(Node &&) = default;
            Node(Node const &) = delete;
            Node & operator=(Node const &) = delete;

            Node(string_type const & = string_type(),
                    ptr_node_type const & = nullptr);
            virtual ~Node();

            id_type const & id() const;
            string_type const & name() const;

            void apply(transform_type const &);
            void apply(rotation_type const &);
            void apply(translation_type const &);
            void apply(scale_type const &);

            transform_type const & local_transform() const;

            node_set_type const & child() const;

            ptr_node_type const & parent() const;
            void parent(ptr_node_type const &);
            void remove_parent();

            bool is_drawn(transform_type const &,
                    rectangle_type const &) const;

            void draw_all(transform_type, rectangle_type const &) const;

        protected:
            virtual void draw(transform_type const &) const;

            static id_type s_current_id;

            id_type         _id;
            string_type     _name;
            transform_type  _local_transform;
            ptr_node_type   _parent;
            node_set_type   _child;
    };
}

#endif

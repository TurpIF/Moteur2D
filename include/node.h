#ifndef SCENE_NODE_H
#define SCENE_NODE_H

#include <set>
#include <mutex>
#include <glm/glm.hpp>

namespace scene {
    class node {
        public:
            typedef glm::mat4 transform_type;
            typedef glm::mediump_float rotation_type;
            typedef glm::vec3 translation_type;
            typedef glm::vec2 scale_type;

            typedef node * ptr_node_type;
            typedef std::set<ptr_node_type> node_set_type;

            typedef std::mutex mutex_type;

            node(node &&) = default;
            node(node const &) = delete;
            node & operator=(node const &) = delete;

            node();
            virtual ~node();

            void apply(transform_type const &);
            void apply(rotation_type const &);
            void apply(translation_type const &);
            void apply(scale_type const &);

            node_set_type const & child() const;

            ptr_node_type const & parent() const;
            void parent(ptr_node_type const &);
            void remove_parent();

            void lock() const;
            void unlock() const;

        protected:
            transform_type _local_transform;

            ptr_node_type _parent;
            node_set_type _child;

            mutable mutex_type _mutex;
    };
}

#endif

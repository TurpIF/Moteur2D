#define GLM_SWIZZLE
#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "node.h"

namespace Scene {
    Node::id_type Node::s_current_id = id_type(0);

    Node::Node(string_type const & __n, ptr_node_type const & __p):
        _id(s_current_id),
        _name(__n),
        _local_transform(1.0),
        _parent(__p),
        _child()
    {
        s_current_id++;
    }

    Node::~Node() {
        for(auto it = _child.begin() ; it != _child.end() ; it++)
            delete *it;
    }

    Node::id_type const & Node::id() const {
        auto const & r = _id;
        return r;
    }

    Node::string_type const & Node::name() const {
        auto const & r = _name;
        return r;
    }

    void Node::apply(transform_type const & __t) {
        _local_transform *= __t;
    }

    void Node::apply(rotation_type const & __a) {
        _local_transform = glm::rotate(_local_transform,
                __a, glm::vec3(0.0, 0.0, 1.0));
    }

    void Node::apply(translation_type const & __v) {
        _local_transform = glm::translate(_local_transform, __v);
    }

    void Node::apply(scale_type const & __s) {
        _local_transform = glm::scale(_local_transform,
                glm::vec3(__s.x, __s.y, 1.0));
    }

    Node::node_set_type const & Node::child() const {
        return _child;
    }

    Node::ptr_node_type const & Node::parent() const {
        return _parent;
    }

    void Node::parent(ptr_node_type const & __p) {
        _parent = __p;
    }

    void Node::remove_parent() {
        _parent = nullptr;
    }
}

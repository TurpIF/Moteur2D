#define GLM_SWIZZLE
#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "node.h"

namespace scene {
    node::node():
        _local_transform(1.0),
        _parent(nullptr),
        _child(),
        _mutex()
    {
    }

    node::~node() {
        _mutex.lock();
        for(auto it = _child.begin() ; it != _child.end() ; it++)
            delete *it;
        _mutex.unlock();
    }

    void node::apply(transform_type const & __t) {
        _mutex.lock();
        _local_transform *= __t;
        _mutex.unlock();
    }

    void node::apply(rotation_type const & __a) {
        _mutex.lock();
        _local_transform = glm::rotate(_local_transform,
                __a, glm::vec3(0.0, 0.0, 1.0));
        _mutex.unlock();
    }

    void node::apply(translation_type const & __v) {
        _mutex.lock();
        _local_transform = glm::translate(_local_transform, __v);
        _mutex.unlock();
    }

    void node::apply(scale_type const & __s) {
        _mutex.lock();
        _local_transform = glm::scale(_local_transform,
                glm::vec3(__s.x, __s.y, 1.0));
        _mutex.unlock();
    }

    node::node_set_type const & node::child() const {
        _mutex.lock();
        auto const & r = _child;
        _mutex.unlock();
        return r;
    }

    node::ptr_node_type const & node::parent() const {
        _mutex.lock();
        auto const & r = _parent;
        _mutex.unlock();
        return r;
    }

    void node::parent(ptr_node_type const & __p) {
        _mutex.lock();
        _parent = __p;
        _mutex.unlock();
    }

    void node::remove_parent() {
        _mutex.lock();
        _parent = nullptr;
        _mutex.unlock();
    }

    void node::lock() const {
        _mutex.lock();
    }

    void node::unlock() const {
        _mutex.unlock();
    }
}

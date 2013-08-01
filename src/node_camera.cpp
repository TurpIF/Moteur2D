#include "node_camera.h"

namespace Scene {
    Camera::Camera(string_type const & __s,
            ptr_node_type const & __p):
        Node(__s, __p),
        _focal(1)
    {
    }

    Camera::~Camera() {
    }

    Camera::scalaire_type const & Camera::focal() const {
        return _focal;
    }

    void Camera::focal(scalaire_type const & __f) {
        _focal = __f;
    }
}

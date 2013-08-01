#include "node_window.h"

#include "node_camera.h"

namespace Scene {
    Window::Window(string_type const & __s,
            ptr_node_type const & __p):
        Node(__s, __p),
        _camera(nullptr)
    {
    }

    Window::~Window() {
    }

    Window::ptr_camera_type const & Window::camera() const {
        return _camera;
    }

    void Window::camera(ptr_camera_type const & __c) {
        _camera = __c;
    }
}

#ifndef SCENE_WINDOW_H
#define SCENE_WINDOW_H

#include "node.h"

namespace Scene {
    class Camera;

    class Window: public Node
    {
        public:
            typedef Camera * ptr_camera_type;

            Window(Window &&) = default;
            Window(Window const &) = delete;
            Window & operator=(Window const &) = delete;

            Window(string_type const & = string_type(),
                    ptr_node_type const & = nullptr);
            virtual ~Window();

            ptr_camera_type const & camera() const;
            void camera(ptr_camera_type const &);

        protected:
            ptr_camera_type _camera;
    };
}

#endif

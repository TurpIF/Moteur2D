#ifndef SCENE_CAMERA_H
#define SCENE_CAMERA_H

#include "node.h"

namespace Scene {
    class Camera: public Node {
        public:
            Camera(Camera &&) = default;
            Camera(Camera const &) = delete;
            Camera & operator=(Camera const &) = delete;

            Camera(string_type const & = string_type(),
                    ptr_node_type const & = nullptr);
            virtual ~Camera();

            scalaire_type const & focal() const;
            void focal(scalaire_type const &);

        protected:
            scalaire_type   _focal;
    };
}

#endif

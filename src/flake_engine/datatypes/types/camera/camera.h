#pragma once

#include "../empty_object.h"

namespace Datatypes {
    struct Camera : EmptyObject {
        float fov = 45.0;
        float near_plane = 0.01;
        float far_plane = 1000.0;

        float freecam_speed = 0.01f;

        glm::mat4 getProjection() {
            return glm::perspective(glm::radians(fov), 800.0f / 600.0f, near_plane, far_plane);
        }

        void handleMovement();
    };
}
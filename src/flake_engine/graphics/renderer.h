#pragma once

#include "../core/window.h"

namespace Flake {
    enum PolygonMode {
        FILL,
        WIREFRAME
    };

    class RenderServer {
    public:
        void setClearColor(float red, float green, float blue);
        void init();
        void clear();
        void render();
        void destroy();

        void setPolygonMode(PolygonMode mode);
    };
}
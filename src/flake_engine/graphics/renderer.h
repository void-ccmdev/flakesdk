#pragma once

#include "../core/window.h"
#include "mesh/mesh.h"
#include "shaders/shader.h"

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
        void draw(Mesh mesh, Shader shader);
        void destroy();

        void setPolygonMode(PolygonMode mode);
    };
}
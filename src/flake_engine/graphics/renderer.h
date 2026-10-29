#pragma once

#include "../core/window.h"
#include "../datatypes/datatypes.h"

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
        void draw(Datatypes::MeshObject meshObject, Shader shader);
        void destroy();

        void setPolygonMode(PolygonMode mode);
    };
}
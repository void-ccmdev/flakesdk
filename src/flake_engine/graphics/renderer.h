#pragma once

#include <glad/glad.h>
#include <vector>
#include "../datatypes/datatypes.h"

namespace Flake {
    enum RenderMode {
        NORMAL,
        WIREFRAME
    };

    class RenderServer {
    public:
        void setClearColor(float red, float green, float blue);
        void clear();
        void setRenderMode(RenderMode mode);
        void initialize();
        void setCamera(Datatypes::Camera& camera);
        void render();
        void addToRenderQueue(Datatypes::MeshObject mesh_object);
    private:
        std::vector<Datatypes::MeshObject> m_render_queue;
        GLuint m_vertexBuffer;
        GLuint m_indexBuffer;
        Datatypes::Camera m_camera;

        GLuint m_index_count = 0;
    };
}
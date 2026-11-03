#pragma once

#include <glad/glad.h>
#include "../datatypes/datatypes.h"

namespace Flake {

    enum RenderMode 
    {
        NORMAL, WIREFRAME
    };

    class RenderServer 
    {
    public:
        void initialize();
        void setRenderMode(RenderMode mode);
        void render();
        void clear();
        void setCamera(Datatypes::Camera& camera);
        void addToQueue(Datatypes::MeshObject object);
    private:
        std::vector<Datatypes::MeshObject> m_render_queue;
        GLuint VAO, VBO, EBO;
        Datatypes::Camera m_camera;
    };
}
#include "renderer.h"

#include "../datatypes/datatypes.h"
#include <iostream>

using namespace Flake;

void RenderServer::setClearColor(float red, float green, float blue)
{
    glClearColor(red, green, blue, 1.0f);
}

void RenderServer::clear() 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderServer::setRenderMode(RenderMode mode) 
{   
    if (mode == RenderMode::NORMAL) { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }
    else if (mode == RenderMode::WIREFRAME) { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }
    else { std::cout<< "Invalid Render mode. Using default Render mode (NORMAL / GL_FILL)" << std::endl; glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }
}

void RenderServer::initialize()
{   
    glEnable(GL_DEPTH_TEST);

    glGenBuffers(1, &m_vertexBuffer);
    glGenBuffers(1, &m_indexBuffer);

    for (Datatypes::MeshObject object : m_render_queue) {
        object.material.shader.load();
        object.material.shader.use();

        glm::mat4 model = object.getTransform();
        glm::mat4 view = glm::inverse(m_camera.getTransform());
        glm::mat4 projection = m_camera.getProjection();

        int modelLoc = glGetUniformLocation(object.material.shader.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        int viewLoc = glGetUniformLocation(object.material.shader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        int projectionLoc = glGetUniformLocation(object.material.shader.ID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(object.mesh.vertices), object.mesh.vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(object.mesh.indices), object.mesh.indices.data(), GL_STATIC_DRAW);

        m_index_count = m_index_count += (GLuint)(sizeof(object.mesh.indices) / sizeof(uint32_t));
    }

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), NULL);

}

void RenderServer::setCamera(Datatypes::Camera& camera) 
{
    m_camera = camera;
}

void RenderServer::addToRenderQueue(Datatypes::MeshObject mesh_object)
{
    m_render_queue.push_back(mesh_object);
}

void RenderServer::render() {
    clear();
    m_camera.handleMovement();
    glDrawElements(GL_TRIANGLES, m_index_count, GL_UNSIGNED_INT, NULL);
}
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
    glEnable(GL_DEPTH_TEST);    // Enable depth test.

    glGenVertexArrays(1, &VAO); // Initialize buffers.
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Datatypes::Vertex) * 1000, nullptr, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * 1000, nullptr, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Datatypes::Vertex), (void*)offsetof(Datatypes::Vertex, position));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Datatypes::Vertex), (void*)offsetof(Datatypes::Vertex, color_rgb));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindVertexArray(0);
}

void RenderServer::pushRenderQueue() 
{   
    GLint prev_vert_size = 0;
    GLint prev_indi_size = 0;

    if (m_render_queue.empty()) { return; }

    for (Datatypes::MeshObject object : m_render_queue)
    {
        object.material.shader.load();
        object.material.shader.use();

        glm::mat4 model = object.getTransform();
        glm::mat4 view = glm::inverse(m_camera.getTransform());
        glm::mat4 projection = m_camera.getProjection();

        int modelLoc = glGetUniformLocation(object.material.shader.ID, "model");
        int viewLoc = glGetUniformLocation(object.material.shader.ID, "view");
        int projectionLoc = glGetUniformLocation(object.material.shader.ID, "projection");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, prev_vert_size, object.mesh.vertices.size() * sizeof(Datatypes::Vertex), object.mesh.vertices.data());

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, prev_indi_size, object.mesh.indices.size() * sizeof(uint32_t), object.mesh.indices.data());

        m_index_count = static_cast<GLsizei>(object.mesh.indices.size());
        prev_vert_size += sizeof(object.mesh.vertices);
        prev_indi_size += sizeof(object.mesh.indices);
    }
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

    pushRenderQueue();

    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, m_index_count, GL_UNSIGNED_INT, NULL);
}
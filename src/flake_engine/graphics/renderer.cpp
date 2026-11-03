#include "renderer.h"

#include <iostream>

using namespace Flake;

void RenderServer::initialize()

{   // Enable depth_test.
    glEnable(GL_DEPTH_TEST);

    // Generate Buffers and Arrays.
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Binding and setting up data for buffers.
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);

    // Inform OpenGL on how the data is made.
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Datatypes::Vertex), reinterpret_cast<void*>(offsetof(Datatypes::Vertex, position)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Datatypes::Vertex), reinterpret_cast<void*>(offsetof(Datatypes::Vertex, color_rgb)));

    // ...
}

void RenderServer::setRenderMode(RenderMode mode)
{   
    if (mode == RenderMode::NORMAL) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    } else if (mode == RenderMode::WIREFRAME) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        std::cout << "Non-existent render mode selected. --> Using RenderMode::NORMAL." << std::endl; 
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

void RenderServer::addToQueue(Datatypes::MeshObject object) { m_render_queue.push_back(object); }

void RenderServer::clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

void RenderServer::setCamera(Datatypes::Camera& camera) { m_camera = camera; }

void RenderServer::render()
{   
    clear();

    if (m_render_queue.empty()) { return; }

    for (auto& object : m_render_queue)
    {
        auto& mesh = object.mesh;

        if (mesh.vertices.empty() || mesh.indices.empty())
            continue;

        object.material.shader.load();
        object.material.shader.use();

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER,static_cast<GLsizeiptr>(mesh.vertices.size() * sizeof(Datatypes::Vertex)),mesh.vertices.data(),GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(mesh.indices.size() * sizeof(uint32_t)), mesh.indices.data(), GL_DYNAMIC_DRAW);
    }
    
    m_camera.handleMovement();

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 100, GL_UNSIGNED_INT, NULL);
}
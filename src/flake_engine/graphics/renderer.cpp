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
    glBufferData(GL_ARRAY_BUFFER, 10000, 0, GL_STREAM_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 10000, 0, GL_STREAM_DRAW);

    // Inform OpenGL on how the data is made.
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Datatypes::Vertex), (void*)offsetof(Datatypes::Vertex, position));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Datatypes::Vertex), (void*)offsetof(Datatypes::Vertex, color_rgb));

    // count of inds anmd verts
    m_used_inds_count = 0;
    m_used_vert_count = 0;

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
        if (!object.rendered) { 
            auto& mesh = object.mesh;

            object.material.shader.load();
            object.material.shader.use();

            // 1. Calculate offsets
            size_t vOffset = m_used_vert_count * sizeof(Datatypes::Vertex);
            size_t iOffset = m_used_inds_count * sizeof(uint32_t);

            // 2. Upload Vertices
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, vOffset, mesh.vertices.size() * sizeof(Datatypes::Vertex), mesh.vertices.data());

            // 3. Offset Indices and Upload
            // We must create a temporary shifted copy of the indices
            std::vector<uint32_t> shiftedIndices = mesh.indices;
            for (auto& index : shiftedIndices) {
                index += m_used_vert_count;
            }

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, iOffset, shiftedIndices.size() * sizeof(uint32_t), shiftedIndices.data());

            // 4. Update persistent counts
            m_used_vert_count += (uint32_t)mesh.vertices.size();
            m_used_inds_count += (uint32_t)mesh.indices.size();
            
            object.rendered = true;
        }
    }
    m_camera.handleMovement();

    glBindVertexArray(VAO);
    //glDrawArrays(GL_TRIANGLES, 0, 100);
    glDrawElements(GL_TRIANGLES, m_used_inds_count, GL_UNSIGNED_INT, NULL);
    
}
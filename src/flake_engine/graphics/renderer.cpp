#include "renderer.h"

#include <glad/glad.h>
#include <cstddef>
#include <iostream>

#include "mesh/mesh.h"
#include "shaders/shader.h"

using namespace Flake;

void RenderServer::setClearColor(float red, float green, float blue) { glClearColor(red, green, blue, 1.0); }
void RenderServer::init() {
    glEnable(GL_DEPTH_TEST);
}

void RenderServer::clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }
void RenderServer::draw(Datatypes::MeshObject meshObject, Shader shader, Datatypes::Camera& camera) {
    shader.use();

    camera.handleMovement();

    glm::mat4 model = meshObject.getTransform();
    glm::mat4 view = glm::inverse(camera.getTransform());
    glm::mat4 projection = camera.getProjection();

    int modelLoc = glGetUniformLocation(shader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    int viewLoc = glGetUniformLocation(shader.ID, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    int projectionLoc = glGetUniformLocation(shader.ID, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    GLuint vertexBufferID;
    glGenBuffers(1, &vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, meshObject.mesh.vertices.size() * sizeof(Vertex), meshObject.mesh.vertices.data(), GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, color)));

    GLuint indexBufferID;
    glGenBuffers(1, &indexBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, meshObject.mesh.indices.size() * sizeof(meshObject.mesh.indices[0]), meshObject.mesh.indices.data(), GL_STATIC_DRAW);

    //std::cout << meshObject.mesh.getVertexCount() << std::endl;
    glDrawElements(GL_TRIANGLES, meshObject.mesh.getVertexCount(), GL_UNSIGNED_SHORT, 0);

    glDeleteBuffers(1, &vertexBufferID);
    glDeleteBuffers(1, &indexBufferID);
}
void RenderServer::destroy() {}

void RenderServer::setPolygonMode(PolygonMode mode) {
    if (mode == PolygonMode::FILL) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    } else if (mode == PolygonMode::WIREFRAME) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        std::cout << "Invalid polygon mode entered. Using default polygon mode. (FILL)" << std::endl;
    }
}
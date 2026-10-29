#include "renderer.h"

#include <glad/glad.h>
#include <cstddef>
#include <iostream>

#include "mesh/mesh.h"
#include "shaders/shader.h"

using namespace Flake;


void RenderServer::setClearColor(float red, float green, float blue) { glClearColor(red, green, blue, 1.0); }
void RenderServer::init() {
    Mesh mesh;
    //mesh.db_createTriangle();


    mesh.vertices = {
        {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}}, //0
        {{ 0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}}, //1
        {{-0.5f,  0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}}, //2
        {{ 0.5f,  0.5f, 0.0f}, {1.0f, 1.0f, 0.0f}}, //3

    };
    mesh.indices = {
        0, 1, 2,
        1, 3, 2
    };

    Shader shader("src\\flake_engine\\graphics\\shaders\\vertex_shader.glsl", "src\\flake_engine\\graphics\\shaders\\fragment_shader.glsl");
    shader.use();



    GLuint vertexBufferID;
    glGenBuffers(1, &vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mesh.vertices) * sizeof(Vertex), mesh.vertices.data(), GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, color)));

    GLuint indexBufferID;
    glGenBuffers(1, &indexBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mesh.indices) * sizeof(Vertex), mesh.indices.data(), GL_STATIC_DRAW);

}
void RenderServer::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}
void RenderServer::render() {
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}
void RenderServer::destroy() {

}


void RenderServer::setPolygonMode(PolygonMode mode) {
    if (mode == PolygonMode::FILL) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    } else if (mode == PolygonMode::WIREFRAME) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        std::cout << "Invalid polygon mode entered. Using default polygon mode. (FILL)" << std::endl;
    }
}
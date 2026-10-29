#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <glad/glad.h>

namespace Flake {
    struct Vertex {
        glm::vec3 position;
        glm::vec3 color;
    };
    
    struct Mesh {
        std::vector<Vertex> vertices;
        std::vector<GLushort> indices;

        void db_createTriangle() {
            vertices = {
                {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},
                {{ 0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}},
                {{ 0.0f,  0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}}
            };
            indices = {0, 1, 2};
        }
    };
}
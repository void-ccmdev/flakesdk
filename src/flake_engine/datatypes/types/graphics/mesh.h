#pragma once

#include "vertex.h"

namespace Datatypes {
    struct Mesh {
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;

        void makeTriangle() {
            vertices = {
                {{-0.5f, -0.5f, -1.0f}, {1.0f, 0.0f, 0.0f}}, //0
                {{ 0.5f, -0.5f, -1.0f}, {0.0f, 1.0f, 0.0f}}, //1
                {{ 0.0f,  0.5f, -1.0f}, {0.0f, 0.0f, 1.0f}}  //2
            };
            indices = {
                0, 1, 2
            };
        }

        void makeQuad() {
            vertices = {
                {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}}, //0
                {{ 0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}}, //1
                {{-0.5f,  0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}}, //2
                {{ 0.5f,  0.5f, 0.0f}, {1.0f, 1.0f, 0.0f}}  //3
            };  
            indices = {
                0, 1, 2, //triangle 1
                1, 3, 2  //triangle 2 
            };
        }
    };
}
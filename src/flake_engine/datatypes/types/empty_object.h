#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>


namespace Datatypes {
    struct EmptyObject {
        std::string name = "EmptyObject";
        
        glm::vec3 position{0.0f};
        glm::vec3 rotation{0.0f};
        glm::vec3 scale{1.0f};

        glm::mat4 getTransform() {
            glm::mat4 model(1.0f);
            
            model = glm::translate(model, position); // Position on XYZ
            model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0)); // Rotation on X
            model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0)); // Rotation on Y
            model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1)); // Rotation on Z
            model = glm::scale(model, scale); // Scale on XYZ

            return model;
        }

        void setPosition(float x, float y, float z) { position = glm::vec3(x,y,z); }
        void setRotation(float x, float y, float z) { rotation = glm::vec3(x, y, z); }
        void setScale(float x, float y, float z) { scale = glm::vec3(x, y ,z); }
    };
}
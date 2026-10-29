#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Datatypes {
    struct EmptyObject {
        std::string name = "EmptyObject";
        
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale = glm::vec3(1.0f);

        glm::mat4 getTransform() {
            glm::mat4 model(1.0f);
            
            model = glm::translate(model, position); // Position on XYZ
            model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0)); // Rotation on X
            model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0)); // Rotation on Y
            model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1)); // Rotation on Z
            model = glm::scale(model, scale); // Scale on XYZ

            return model;
        }
    };
}
#include "camera.h"

using namespace Datatypes;

void Camera::handleMovement() {
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS) {
        position += glm::vec3(0, 0, -1) * freecam_speed;
    }
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS) {
        position += glm::vec3(-1, 0, 0) * freecam_speed;
    }
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS) {
        position += glm::vec3(0, 0, 1) * freecam_speed;
    }
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS) {
        position += glm::vec3(1, 0, 0) * freecam_speed;
    }

    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_SPACE) == GLFW_PRESS) {
        position += glm::vec3(0, 1, 0) * freecam_speed;
    }
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        position += glm::vec3(0, -1, 0) * freecam_speed;
    }
}
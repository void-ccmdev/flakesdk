#include "window.h"
#include <stdexcept>

using namespace Flake;

//- Window Server Class

WindowServer::~WindowServer()
{
    glfwTerminate();
}
void WindowServer::createWindow(WindowObject& window) 
{
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW!");
    }

    glfwWindowHint(GLFW_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GLFW_TRUE);

    if (window.state == WindowState::maximized) { glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE); }
    else if (window.state == WindowState::windowed) { glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE); }

    window.glfw_window = glfwCreateWindow(window.width, window.height, window.title.c_str(), nullptr, nullptr);
    if (!window.glfw_window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create a GLFW window!");
    }
    glfwMakeContextCurrent(window.glfw_window);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        glfwDestroyWindow(window.glfw_window);
        window.glfw_window = nullptr;
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLAD!");
    }
}
void WindowServer::updateWindow(WindowObject& window)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window.glfw_window);
    glfwPollEvents();
}
void WindowServer::closeWindow(WindowObject& window)
{
    glfwDestroyWindow(window.glfw_window);
}
void WindowServer::changeWindowTitle(std::string& new_title, WindowObject& window)
{
    glfwSetWindowTitle(window.glfw_window, new_title.c_str());
}
GLFWwindow* WindowServer::getCurrentWindow() const
{
    return glfwGetCurrentContext();
}
bool WindowServer::shouldWindowClose(WindowObject& window) const
{
    return glfwWindowShouldClose(window.glfw_window);
}
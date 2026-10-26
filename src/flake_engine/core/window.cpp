#include "window.h"
#include <stdexcept>

using namespace Flake;

//- Window Server Class

void WindowServer::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    auto* owner = static_cast<WindowServer*>(glfwGetWindowUserPointer(window));
    if (owner != nullptr) {
        owner->m_framebufferWidth = width;
        owner->m_framebufferHeight = height;
    }
    glViewport(0, 0, width, height);
}
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
    glfwSetWindowUserPointer(window.glfw_window, this);
    glfwSetFramebufferSizeCallback(window.glfw_window, framebufferSizeCallback);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        glfwDestroyWindow(window.glfw_window);
        window.glfw_window = nullptr;
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLAD!");
    }

    glfwGetFramebufferSize(window.glfw_window, &m_framebufferWidth, &m_framebufferHeight);
    glViewport(0, 0, m_framebufferWidth, m_framebufferHeight);
}
void WindowServer::updateWindow(WindowObject& window)
{
    glfwSwapBuffers(window.glfw_window);

    glfwGetFramebufferSize(window.glfw_window, &m_framebufferWidth, &m_framebufferHeight);
    glViewport(0, 0, m_framebufferWidth, m_framebufferHeight);

    glClear(GL_COLOR_BUFFER_BIT);
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
void WindowServer::setWindowShouldClose(WindowObject& window, bool value) {
    glfwSetWindowShouldClose(window.glfw_window, value);
}
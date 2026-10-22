#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "string"

namespace Flake {

    enum WindowState {
        windowed,
        maximized,
        //fullscreen
    };

    struct WindowObject {   
        int width, height = 500;
        std::string title = "Flake window";
        GLFWwindow* glfw_window = nullptr;
        WindowState state = WindowState::windowed;
    };

    class WindowServer {
    public:
        ~WindowServer();

        void createWindow(WindowObject& window);
        void updateWindow(WindowObject& window);
        void closeWindow(WindowObject& window);

        void changeWindowTitle(std::string& new_title, WindowObject& window);
        GLFWwindow* getCurrentWindow() const;
        bool shouldWindowClose(WindowObject& window) const;
    };

}   //namespace Flake
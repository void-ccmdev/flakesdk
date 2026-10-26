#pragma once 

#include <GLFW/glfw3.h>
#include <string>

namespace Flake {
    struct InputMod {
        bool alt = false;
        bool ctrl = false;
        bool shift = false;
        bool super = false;
    };

    enum InputDevice {
        KEYBOARD,
        MOUSE
    };

    struct InputEvent {
        using Action = void (*)();

        std::string event_name = "";
        InputDevice device;
        int glfw_key;
        InputMod mod;
        int glfw_key_state = GLFW_PRESS;
        Action action = nullptr;
    };

    class InputServer {
    public:
        void addEvent(InputEvent new_event);
        void processInput(GLFWwindow* window);
    private:
        InputEvent events[32];
        unsigned int eventsCount = 0;
    };
}
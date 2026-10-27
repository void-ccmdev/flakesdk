#include "flake_engine/flake_engine.h"

Flake::WindowServer windowServer;
Flake::UIServer uiServer;
Flake::InputServer inputServer;
Flake::FileServer fileServer;
Flake::GlobalServer globalServer;

//------------------------------------\\

Flake::WindowObject mainWindow;
Flake::InputEvent forceQuit;

void forceQuitAction() {
    windowServer.setWindowShouldClose(mainWindow, true);
}

int main(void)
{   
    {
        mainWindow.width = 1280;
        mainWindow.height = 720;
        mainWindow.title = "Flake Editor";
        mainWindow.state = Flake::WindowState::windowed;
    }
    windowServer.createWindow(mainWindow);
    {
        forceQuit.event_name = std::string("force_quit");
        forceQuit.device = Flake::InputDevice::KEYBOARD;
        forceQuit.glfw_key = GLFW_KEY_END;
        forceQuit.mod.alt = true;
        forceQuit.action = forceQuitAction;
    }
    inputServer.addEvent(forceQuit);

    uiServer.ui_init();
    uiServer.ui_set_style(Flake::UIStyle::DARK);

    while (!windowServer.shouldWindowClose(mainWindow)) {
        inputServer.processInput(mainWindow.glfw_window);
        uiServer.ui_begin();

        uiServer.ui_end();
        windowServer.updateWindow(mainWindow);
    }

    uiServer.ui_destroy();
    windowServer.closeWindow(mainWindow);

    return 0;
}
#include "flake_engine/flake_engine.h"

inline Flake::WindowServer windowServer;

int main()
{   
    Flake::WindowObject mainWindow;
    {
        mainWindow.width = 1280;
        mainWindow.height = 720;
        mainWindow.title = "Flake Editor";
        mainWindow.state = Flake::WindowState::windowed;
    }

    windowServer.createWindow(mainWindow);

    while (!windowServer.shouldWindowClose(mainWindow)) {
        windowServer.updateWindow(mainWindow);
    }

    windowServer.closeWindow(mainWindow);

    return 0;
}
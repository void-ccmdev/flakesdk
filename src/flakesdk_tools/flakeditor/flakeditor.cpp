#include "flake_engine/flake_engine.h"

inline Flake::WindowServer windowServer;
inline Flake::UIServer uiServer;

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

    uiServer.ui_init();

    while (!windowServer.shouldWindowClose(mainWindow)) {
        uiServer.ui_begin();

        ImGui::Begin("Wassup bejing!", nullptr, ImGuiWindowFlags_NoCollapse);
        ImGui::Text("This is raah!");
        ImGui::End();

        uiServer.ui_end();
        windowServer.updateWindow(mainWindow);
    }

    uiServer.ui_destroy();
    windowServer.closeWindow(mainWindow);

    return 0;
}
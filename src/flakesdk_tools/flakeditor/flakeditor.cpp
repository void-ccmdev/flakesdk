#include "flake_engine/flake_engine.h"

Flake::WindowServer windowServer;
Flake::UIServer uiServer;
Flake::InputServer inputServer;
Flake::FileServer fileServer;
Flake::GlobalServer globalServer;
Flake::RenderServer renderServer;

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

    renderServer.init();
    //renderServer.setClearColor(1.0f, 0.0f, 0.0f);
    //renderServer.setPolygonMode(Flake::PolygonMode::WIREFRAME);

    bool wireframe = false;

    uiServer.ui_init(); 
    uiServer.ui_set_style(Flake::UIStyle::DARK);

    Flake::Mesh quad;
    quad.db_createQuad();
    Flake::Mesh triangle;
    triangle.db_createTriangle();
    Flake::Shader shader("src\\flake_engine\\graphics\\shaders\\vertex_shader.glsl", "src\\flake_engine\\graphics\\shaders\\fragment_shader.glsl");

    while (!windowServer.shouldWindowClose(mainWindow)) {
        
        inputServer.processInput(mainWindow.glfw_window);

        renderServer.setClearColor(0.1f, 0.1f, 0.1f);
        renderServer.clear();
        renderServer.draw(quad, shader);   
        renderServer.draw(triangle, shader); 

        uiServer.ui_begin();

        ImGui::Begin("Settings");
        ImGui::Checkbox("Wireframe", &wireframe);
        ImGui::End();
        
        if (wireframe) {
            renderServer.setPolygonMode(Flake::PolygonMode::WIREFRAME);
        } else {
            renderServer.setPolygonMode(Flake::PolygonMode::FILL);
        }

        uiServer.ui_end();
        windowServer.updateWindow(mainWindow);
    }

    uiServer.ui_destroy();
    windowServer.closeWindow(mainWindow);

    return 0;
}
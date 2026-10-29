#include "flake_engine/flake_engine.h"

Flake::WindowServer windowServer;
Flake::UIServer uiServer;
Flake::InputServer inputServer;
Flake::FileServer fileServer;
inline Flake::GlobalServer globalServer;
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
    float v = 0.0f;
    float d = -2.0f;
    float s = 1.0f;
    float x = 0.0f;

    uiServer.ui_init(); 
    uiServer.ui_set_style(Flake::UIStyle::DARK);

    Datatypes::MeshObject mesh_object;
    Flake::Mesh quad;
    quad.db_createTriangle();
    mesh_object.mesh = quad;
    Flake::Shader shader("src\\flake_engine\\graphics\\shaders\\vertex_shader.glsl", "src\\flake_engine\\graphics\\shaders\\fragment_shader.glsl");

    Datatypes::Camera camera;
    mesh_object.setPosition(0,0,d);
    

    while (!windowServer.shouldWindowClose(mainWindow)) {
        inputServer.processInput(mainWindow.glfw_window);

        renderServer.setClearColor(0.1f, 0.1f, 0.1f);
        renderServer.clear();
        renderServer.draw(mesh_object, shader, camera);   
        mesh_object.position = glm::vec3(x, 0, d);
        mesh_object.rotation = glm::vec3(0, v, 0);
        mesh_object.scale = glm::vec3(s, s, s);
        
        //mesh_object.rotation += mesh_object.rotation + glm::vec3(0, 0, (float)glfwGetTime() * 90000);

        uiServer.ui_begin();

        ImGui::Begin("Settings");
        ImGui::Checkbox("Wireframe", &wireframe);
        ImGui::SliderFloat("posx", &x, -10.0f, 10.0f);
        ImGui::SliderFloat("posz", &d, -10.0f, 10.0f);
        ImGui::SliderFloat("scale", &s, -10.0f, 10.0f);
        ImGui::SliderFloat("rot", &v, -360.0f, 360.0f);
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
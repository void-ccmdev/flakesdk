#include "flake_engine/flake_engine.h"

Flake::WindowServer windowServer;
Flake::RenderServer renderServer;
Flake::UIServer uiServer;
Flake::InputServer inputServer;
Flake::FileServer fileServer;
inline Flake::GlobalServer globalServer;

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

    //Set up rendering

    renderServer.initialize();
    renderServer.setRenderMode(Flake::RenderMode::WIREFRAME);

    //Create a mesh with a material
    Datatypes::MeshObject mesh;
    Datatypes::Material material;
    Datatypes::Shader shader;
    Datatypes::Camera camera;

    //Setup shaders
    Flake::File vert_shader;
    Flake::File frag_shader;
    vert_shader.path = std::string("src/flake_engine/graphics/shaders/default_vertex_shader.glsl");
    frag_shader.path = std::string("src/flake_engine/graphics/shaders/default_fragment_shader.glsl");

    shader.vertex_shader_file = vert_shader;
    shader.fragment_shader_file = frag_shader;

    //Setup material
    material.shader = shader;
    mesh.material = material;

    //Setup mesh
    mesh.mesh.makeQuad();
    
    //Add mesh to render queue
    renderServer.addToQueue(mesh);
    renderServer.setCamera(camera);

    //Sliders
    float x = 0.0f;
    bool wir = 0;

    while (!windowServer.shouldWindowClose(mainWindow)) {
        //mesh.setPosition(x, 0.0f, 0.0f);

        inputServer.processInput(mainWindow.glfw_window);

        renderServer.render();

        uiServer.ui_begin();

        ImGui::Begin("Settings");
        //ImGui::SliderFloat("xpos", &x, -10.0f, 10.0f);
        ImGui::Checkbox("Wireframe", &wir);
        ImGui::End();

        uiServer.ui_end();
        windowServer.updateWindow(mainWindow);

        if (wir) { renderServer.setRenderMode(Flake::RenderMode::WIREFRAME); }
        else { renderServer.setRenderMode(Flake::RenderMode::NORMAL); }
    }

    uiServer.ui_destroy();
    windowServer.closeWindow(mainWindow);

    return 0;
}
#include "ui.h"

#include <iostream>
#include <GLFW/glfw3.h>

using namespace Flake;

void UIServer::ui_init() 
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    m_io = &ImGui::GetIO();

    m_io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    m_io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    m_io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    m_io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui_ImplGlfw_InitForOpenGL(glfwGetCurrentContext(), true);
    ImGui_ImplOpenGL3_Init("#version 330");
}
void UIServer::ui_begin() 
{
    glfwPollEvents();
    if (glfwGetWindowAttrib(glfwGetCurrentContext(), GLFW_ICONIFIED) != 0) {
        ImGui_ImplGlfw_Sleep(10);
    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::DockSpaceOverViewport(0,
        ImGui::GetMainViewport(),
        ImGuiDockNodeFlags_PassthruCentralNode
    );
}
void UIServer::ui_set_style(UIStyle style) 
{
    if (style == UIStyle::DARK) { ImGui::StyleColorsDark(); }
    else if (style == UIStyle::LIGHT) { ImGui::StyleColorsLight(); }
    else if (style == UIStyle::CLASSIC) { ImGui::StyleColorsClassic(); }
    else { std::cout << "No UI style selected -> using default style. (DARK)" << std::endl; ImGui::StyleColorsDark(); }

    m_mainScale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());
    ImGuiStyle& imGuiStyle = ImGui::GetStyle();
    imGuiStyle.ScaleAllSizes(m_mainScale);
    imGuiStyle.FontScaleDpi = m_mainScale;

    if (m_io && (m_io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable))
    {
        imGuiStyle.WindowRounding = 0.0f;
        imGuiStyle.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }
}
void UIServer::ui_end() 
{
    ImGui::Render();

    if (m_io && (m_io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)) {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
void UIServer::ui_destroy() 
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_stdlib.h"

namespace Flake {
    enum UIStyle {
        DARK,
        LIGHT,
        CLASSIC
    };

    class UIServer {
    public:
        void ui_init();
        void ui_set_style(UIStyle style);
        void ui_begin();
        void ui_end();
        void ui_destroy();
    private:
        float m_mainScale = 1.0f;
        ImGuiIO* m_io = nullptr;
    };
}
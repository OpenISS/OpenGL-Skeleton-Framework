#include "imgui_integration.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../thirdparty/imgui/imgui_impl_glfw.h"
#include "../thirdparty/imgui/imgui_impl_opengl3.h"
#include "../world.h"

void ImGuiIntegration::Startup(World& world)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(world.getWindow()), true);
    ImGui_ImplOpenGL3_Init("#version 150");

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
}

void ImGuiIntegration::Shutdown(World& world)
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImGuiIntegration::PreRender(World& world)
{
    // Feed inputs, start new frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGuiIO &io = ImGui::GetIO();

    // Handle cursor wrap around window edges
    const int w = world.windowWidth;
    const int h = world.windowHeight;
    io.MousePos.x = io.MousePos.x - static_cast<float>(static_cast<int>(io.MousePos.x / w) * w);
    io.MousePos.y = io.MousePos.y - static_cast<float>(static_cast<int>(io.MousePos.y / h) * h);
    if (io.MousePos.x < 0)
        io.MousePos.x += static_cast<float>(w);
    if (io.MousePos.y < 0)
        io.MousePos.y += static_cast<float>(h);

    ImGui::NewFrame();
}

void ImGuiIntegration::PostRender(World& world)
{
    // Our native window cursor is invisible, so ask imgui to render another one
    ImGui::GetIO().MouseDrawCursor = enabled;

    // Render into screen
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool ImGuiIntegration::wantCaptureMouse()
{
    return ImGui::GetIO().WantCaptureMouse && enabled;
}

bool ImGuiIntegration::wantCaptureKeyboard()
{
    return ImGui::GetIO().WantCaptureKeyboard && enabled;
}

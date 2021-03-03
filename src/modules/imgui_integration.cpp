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
    glfwSetInputMode(static_cast<GLFWwindow*>(world.getWindow()), GLFW_CURSOR, enabled ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);

    // Feed inputs, start new frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiIntegration::PostRender(World& world)
{
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

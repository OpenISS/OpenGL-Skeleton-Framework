#pragma once
#include <vector>
#include "camera.h"
#include "light_data.h"
#include "mesh.h"
#include "modules/imgui_integration.h"
#include "modules/rendering_mode.h"
#include "modules/scene_graph.h"
#include "modules/shadows.h"
#include "shader.h"

enum class RenderPass
{
    Color,
    Shadow
};

/**
 * Manages all modules. Contains global state like the SceneGraph and the Camera.
 * 
 * Add new modules inside World::AddModules().
 */
class World
{
public:

    World();

    void Startup(void* window);
    void Shutdown();

    void Update(float deltaSeconds);
    void Render();

    void OnKey(int key, int action, int mods);
    int GetKey(int key) { return glfwGetKey(static_cast<GLFWwindow*>(window), key); };

    void OnMouseMoved(float x, float y);
    void OnMousePressed(int button, int mods);
    void OnMouseReleased(int button, int mods);

    /// Window object from the window library currently in use (ex: GLFW), cast as needed
    void* getWindow() const { return window; }

    /// Total seconds elapsed since the application started
    float getTime() const { return time; }

    std::vector<Module*> modules = std::vector<Module*>();

    ImGuiIntegration* imgui;
    RenderingMode* renderingMode;
    SceneGraph* sceneGraph;
    Camera* camera;
    Shadows* shadows;

    std::vector<LightData*> lights;

    int windowWidth;
    int windowHeight;
    float windowAspectRatio;
    int windowSamples;
    const char* windowTitle;
    bool debug = false;

protected:

    void AddModules();

    void* window = nullptr;
    float time = 0.0f;

    float lastMouseX = 0.0f;
    float lastMouseY = 0.0f;

    // Short workaround for avoiding huge camera motion on initial mouse movement
    bool skipNextMouseDelta = true;
};

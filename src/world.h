#pragma once
#include <vector>
#include "camera.h"
#include "mesh.h"
#include "modules/imgui_integration.h"
#include "modules/rendering_mode.h"
#include "modules/scene_graph.h"
#include "shader.h"

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

    void OnMouseMoved(float x, float y);
    void OnMousePressed(int button, int mods);
    void OnMouseReleased(int button, int mods);

    /// Window object from the window library currently in use (ex: GLFW), cast as needed
    void* getWindow() const { return window; }

    /// Total seconds elapsed since the application started
    float getTime() const { return time; }

    ImGuiIntegration* imgui;
    RenderingMode* renderingMode;
    SceneGraph* sceneGraph;
    Camera* camera;

    int windowWidth;
    int windowHeight;
    float windowAspectRatio;
    int windowSamples;
    const char* windowTitle;
    bool debug = false;

protected:

    void AddModules();

    std::vector<Module*> modules = std::vector<Module*>();
    void* window = nullptr;
    float time = 0.0f;
};
